#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_3__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_1__ QSYNTH_SEGMENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  qsynth_read_event (scalar_t__,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T qsynth_read_track(QSYNTH_SEGMENT_T *seg,
                                               uint32_t *ticks, int64_t *time,
                                               uint32_t *us_perclock, uint32_t *tempo_ticks)
{
   uint32_t total_ticks = 0;
   uint32_t used = 8;
   uint8_t last = 0;

   *time = 0LL;
   *tempo_ticks = 0;

   while(used < seg->len)
   {
      VC_CONTAINER_STATUS_T status;
      uint32_t event_ticks, new_tempo = 0, end = 0, event_used;
      if((status = qsynth_read_event(seg->data+used, &event_used, &last, &event_ticks, &new_tempo, &end)) != VC_CONTAINER_SUCCESS)
         return status;

      used += event_used;
      total_ticks += event_ticks;

      if(new_tempo != 0)
      {
         *time += ((int64_t) (total_ticks - *tempo_ticks)) * (*us_perclock);
         *us_perclock = new_tempo;
         *tempo_ticks = total_ticks;
      }

      if(end)
         break;
   }

   *ticks = total_ticks;
   return VC_CONTAINER_SUCCESS;
}