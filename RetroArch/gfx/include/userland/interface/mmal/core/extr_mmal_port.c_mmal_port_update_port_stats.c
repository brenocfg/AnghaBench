#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int first_buffer_time; unsigned int last_buffer_time; int /*<<< orphan*/  max_delay; int /*<<< orphan*/  buffer_count; } ;
struct TYPE_7__ {TYPE_5__ tx; TYPE_5__ rx; } ;
struct TYPE_10__ {int /*<<< orphan*/  stats_lock; TYPE_1__ stats; } ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {TYPE_4__* core; } ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_PORT_PRIVATE_CORE_T ;
typedef  scalar_t__ MMAL_CORE_STATS_DIR ;
typedef  TYPE_5__ MMAL_CORE_STATISTICS_T ;

/* Variables and functions */
 scalar_t__ MMAL_CORE_STATS_RX ; 
 unsigned int vcos_getmicrosecs () ; 
 int /*<<< orphan*/  vcos_max (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmal_port_update_port_stats(MMAL_PORT_T *port, MMAL_CORE_STATS_DIR direction)
{
   MMAL_PORT_PRIVATE_CORE_T *core = port->priv->core;
   MMAL_CORE_STATISTICS_T *stats;
   unsigned stc = vcos_getmicrosecs();

   vcos_mutex_lock(&core->stats_lock);

   stats = direction == MMAL_CORE_STATS_RX ? &core->stats.rx : &core->stats.tx;

   stats->buffer_count++;

   if (!stats->first_buffer_time)
   {
      stats->last_buffer_time = stats->first_buffer_time = stc;
   }
   else
   {
      stats->max_delay = vcos_max(stats->max_delay, stc-stats->last_buffer_time);
      stats->last_buffer_time = stc;
   }
   vcos_mutex_unlock(&core->stats_lock);
}