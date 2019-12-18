#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_16__ {TYPE_9__ time; } ;
struct TYPE_25__ {int* ptr; int /*<<< orphan*/  len; } ;
struct TYPE_24__ {int channel; int param; int value; } ;
struct TYPE_23__ {int channel; int note; int velocity; } ;
struct TYPE_26__ {TYPE_6__ ext; TYPE_5__ control; TYPE_4__ note; } ;
struct TYPE_22__ {int /*<<< orphan*/  client; } ;
struct TYPE_20__ {int /*<<< orphan*/  port; } ;
struct TYPE_17__ {scalar_t__ type; int flags; TYPE_10__ time; TYPE_7__ data; TYPE_3__ dest; TYPE_1__ source; int /*<<< orphan*/  queue; } ;
typedef  TYPE_11__ snd_seq_event_t ;
struct TYPE_18__ {int* data; int delta_time; int /*<<< orphan*/  data_size; } ;
typedef  TYPE_12__ midi_event_t ;
struct TYPE_27__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_21__ {int /*<<< orphan*/  port; } ;
struct TYPE_19__ {TYPE_8__ out_ev_time; int /*<<< orphan*/  seq; TYPE_2__ out_src; int /*<<< orphan*/  out_queue; } ;
typedef  TYPE_13__ alsa_midi_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,int) ; 
 int /*<<< orphan*/  SND_SEQ_ADDRESS_SUBSCRIBERS ; 
 scalar_t__ SND_SEQ_EVENT_CHANPRESS ; 
 scalar_t__ SND_SEQ_EVENT_CONTROLLER ; 
 scalar_t__ SND_SEQ_EVENT_KEYPRESS ; 
 int SND_SEQ_EVENT_LENGTH_VARIABLE ; 
 scalar_t__ SND_SEQ_EVENT_NOTEOFF ; 
 scalar_t__ SND_SEQ_EVENT_NOTEON ; 
 scalar_t__ SND_SEQ_EVENT_PGMCHANGE ; 
 scalar_t__ SND_SEQ_EVENT_PITCHBEND ; 
 scalar_t__ SND_SEQ_EVENT_SYSEX ; 
 int SND_SEQ_TIME_MODE_ABS ; 
 int SND_SEQ_TIME_STAMP_REAL ; 
 scalar_t__* alsa_midi_ev_map ; 
 int snd_seq_event_output (int /*<<< orphan*/ ,TYPE_11__*) ; 

__attribute__((used)) static bool alsa_midi_write(void *p, const midi_event_t *event)
{
   int r;
   snd_seq_event_t ev;
   alsa_midi_t *d = (alsa_midi_t*)p;

   ev.type  = alsa_midi_ev_map[(event->data[0] >> 4) & 7];
   ev.flags = SND_SEQ_TIME_STAMP_REAL | SND_SEQ_TIME_MODE_ABS;
   ev.queue = d->out_queue;
   ev.time.time.tv_sec  = d->out_ev_time.tv_sec + event->delta_time / 1000000;
   ev.time.time.tv_nsec = d->out_ev_time.tv_nsec +
         (event->delta_time % 1000000) * 1000;
   if(ev.time.time.tv_nsec >= 1000000000)
   {
       ev.time.time.tv_sec  += 1;
       ev.time.time.tv_nsec -= 1000000000;
   }
   ev.source.port = d->out_src.port;
   ev.dest.client = SND_SEQ_ADDRESS_SUBSCRIBERS;

   if (ev.type == SND_SEQ_EVENT_NOTEOFF || ev.type == SND_SEQ_EVENT_NOTEON ||
         ev.type == SND_SEQ_EVENT_KEYPRESS)
   {
      ev.data.note.channel  = event->data[0] & 0x0F;
      ev.data.note.note     = event->data[1];
      ev.data.note.velocity = event->data[2];
   }
   else if (ev.type == SND_SEQ_EVENT_CONTROLLER)
   {
      ev.data.control.channel = event->data[0] & 0x0F;
      ev.data.control.param   = event->data[1];
      ev.data.control.value   = event->data[2];
   }
   else if (ev.type == SND_SEQ_EVENT_PGMCHANGE ||
         ev.type == SND_SEQ_EVENT_CHANPRESS)
   {
      ev.data.control.channel = event->data[0] & 0x0F;
      ev.data.control.value   = event->data[1];
   }
   else if (ev.type == SND_SEQ_EVENT_PITCHBEND)
   {
      ev.data.control.channel = event->data[0] & 0x0F;
      ev.data.control.value   = (event->data[1] | (event->data[2] << 7)) - 0x2000;
   }
   else if (ev.type == SND_SEQ_EVENT_SYSEX)
   {
      ev.flags |= SND_SEQ_EVENT_LENGTH_VARIABLE;
      ev.data.ext.ptr = event->data;
      ev.data.ext.len = event->data_size;
   }

   r = snd_seq_event_output(d->seq, &ev);
#ifdef DEBUG
   if (r < 0)
      RARCH_ERR("[MIDI]: snd_seq_event_output failed with error %d.\n", r);
#endif

   d->out_ev_time.tv_sec  = ev.time.time.tv_sec;
   d->out_ev_time.tv_nsec = ev.time.time.tv_nsec;

   return r >= 0;
}