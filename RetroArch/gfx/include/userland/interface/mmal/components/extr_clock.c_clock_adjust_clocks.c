#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int count; int length; } ;
struct TYPE_20__ {scalar_t__ mt_off_avg; int mt_off_std; TYPE_2__ avg_filter; int /*<<< orphan*/  id; } ;
struct TYPE_15__ {scalar_t__ target; scalar_t__ attack_rate; scalar_t__ attack_period; } ;
struct TYPE_19__ {scalar_t__ stc_at_update; scalar_t__ mt_off_clk; scalar_t__ mt_off_target; scalar_t__ frame_duration; scalar_t__ adj_p; int adj_m; int frame_rate_log2; int adj; int /*<<< orphan*/  scale; scalar_t__ pending_scale; TYPE_1__ latency; scalar_t__ clock_discont; int /*<<< orphan*/  stream_max_id; int /*<<< orphan*/  stream_min_id; } ;
struct TYPE_18__ {TYPE_3__* priv; int /*<<< orphan*/ * clock; } ;
struct TYPE_17__ {TYPE_5__* module; } ;
typedef  scalar_t__ TIME_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;
typedef  TYPE_5__ MMAL_COMPONENT_MODULE_T ;
typedef  TYPE_6__ CLOCK_STREAM_T ;

/* Variables and functions */
 int MAX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ MMAL_FALSE ; 
 int /*<<< orphan*/  clock_get_mt_off_avg (TYPE_4__*,scalar_t__,TYPE_6__**,TYPE_6__**) ; 
 int /*<<< orphan*/  clock_set_media_time (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  clock_set_scale (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_start_clocks (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  clock_stop_clocks (TYPE_4__*) ; 
 scalar_t__ mmal_port_clock_media_time_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clock_adjust_clocks(MMAL_COMPONENT_T *component, TIME_T stc)
{
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   CLOCK_STREAM_T *stream_min;
   CLOCK_STREAM_T *stream_max;
   TIME_T mt_off_clk;
   TIME_T stc_prev;

   if (!clock_get_mt_off_avg(component, stc, &stream_min, &stream_max))
      return;

   module->stream_min_id = stream_min->id;
   module->stream_max_id = stream_max->id;

   /* Calculate the actual media-time offset seen by the clock */
   mt_off_clk = mmal_port_clock_media_time_get(component->clock[0]) - stc;

   stc_prev = module->stc_at_update;
   module->stc_at_update = stc;

   /* If there has been a discontinuity, restart the clock,
    * else use the clock control loop to apply a clock adjustment */
   if (module->clock_discont)
   {
      module->clock_discont = MMAL_FALSE;

      module->mt_off_clk = stream_min->mt_off_avg - module->latency.target;
      module->mt_off_target = module->mt_off_clk;

      clock_stop_clocks(component);
      clock_start_clocks(component, module->mt_off_clk + stc);
   }
   else
   {
      /* Determine the new clock target */
      TIME_T mt_off_target_max = stream_max->mt_off_avg - module->latency.target;
      TIME_T mt_off_target_min = stream_min->mt_off_avg - module->frame_duration;
      module->mt_off_target = MIN(mt_off_target_max, mt_off_target_min);

      /* Calculate the proportional adjustment, capped by the attack rate
       * set by the client */
      TIME_T stc_delta = (stc > stc_prev) ? (stc - stc_prev) : 0;
      TIME_T adj_p_max = stc_delta * module->latency.attack_rate / module->latency.attack_period;

      module->adj_p = module->mt_off_target - module->mt_off_clk;
      if (module->adj_p < -adj_p_max)
         module->adj_p = -adj_p_max;
      else if (module->adj_p > adj_p_max)
         module->adj_p = adj_p_max;

      /* Calculate the confidence of the adjustment using the approximate
       * standard deviation for the selected stream:
       *
       * adj_m = 1.0 - STD * FPS / 4
       *
       * The adjustment factor is scaled up by 2^20 which is an approximation
       * of 1000000 (microseconds per second) and the frame rate is assumed
       * to be either 32 or 64 which are approximations for 24/25/30 and 60
       * fps to avoid divisions.  This has a lower limit of 0. */
      module->adj_m =
         MAX((1 << 20) - ((stream_min->mt_off_std << module->frame_rate_log2) >> 2), 0);

      /* Modulate the proportional adjustment by the sample confidence
       * and apply the adjustment to the current clock */
      module->adj = (module->adj_p * module->adj_m) >> 20;
      module->adj = (module->adj * (stream_min->avg_filter.count << 8) / stream_min->avg_filter.length) >> 8;
      module->mt_off_clk += module->adj;

      clock_set_media_time(component, module->mt_off_clk + stc);
   }

   /* Any pending clock scale changes can now be applied */
   if (component->priv->module->pending_scale)
      clock_set_scale(component, component->priv->module->scale);
}