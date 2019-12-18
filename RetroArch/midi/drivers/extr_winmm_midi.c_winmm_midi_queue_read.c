#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t rd_idx; size_t wr_idx; TYPE_2__* events; } ;
typedef  TYPE_1__ winmm_midi_queue_t ;
struct TYPE_6__ {unsigned int data_size; int /*<<< orphan*/  delta_time; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ midi_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int WINMM_MIDI_BUF_LEN ; 

__attribute__((used)) static bool winmm_midi_queue_read(winmm_midi_queue_t *q, midi_event_t *ev)
{
   unsigned i;
   midi_event_t *src_ev = NULL;

   if (q->rd_idx == q->wr_idx)
      return false;

   if (ev->data_size < q->events[q->rd_idx].data_size)
   {
#ifdef DEBUG
      RARCH_ERR("[MIDI]: Input queue read failed (event data too small).\n");
#endif
      return false;
   }

   src_ev = &q->events[q->rd_idx];

   for (i = 0; i < src_ev->data_size; ++i)
      ev->data[i] = src_ev->data[i];

   ev->data_size = src_ev->data_size;
   ev->delta_time = src_ev->delta_time;

   if (q->rd_idx + 1 == WINMM_MIDI_BUF_LEN)
      q->rd_idx = 0;
   else
      ++q->rd_idx;

   return true;
}