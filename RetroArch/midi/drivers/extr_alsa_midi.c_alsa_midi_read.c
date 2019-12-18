#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_13__ {int len; scalar_t__ ptr; } ;
struct TYPE_12__ {int channel; int param; int value; } ;
struct TYPE_11__ {int channel; int note; int velocity; } ;
struct TYPE_14__ {TYPE_3__ ext; TYPE_2__ control; TYPE_1__ note; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_4__ data; } ;
typedef  TYPE_5__ snd_seq_event_t ;
struct TYPE_16__ {int* data; int data_size; scalar_t__ delta_time; } ;
typedef  TYPE_6__ midi_event_t ;
struct TYPE_17__ {int /*<<< orphan*/  seq; } ;
typedef  TYPE_7__ alsa_midi_t ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 scalar_t__ SND_SEQ_EVENT_CHANPRESS ; 
 scalar_t__ SND_SEQ_EVENT_CONTROLLER ; 
 scalar_t__ SND_SEQ_EVENT_KEYPRESS ; 
 scalar_t__ SND_SEQ_EVENT_NOTEOFF ; 
 scalar_t__ SND_SEQ_EVENT_NOTEON ; 
 scalar_t__ SND_SEQ_EVENT_PGMCHANGE ; 
 scalar_t__ SND_SEQ_EVENT_PITCHBEND ; 
 scalar_t__ SND_SEQ_EVENT_SYSEX ; 
 int snd_seq_event_input (int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  snd_seq_free_event (TYPE_5__*) ; 

__attribute__((used)) static bool alsa_midi_read(void *p, midi_event_t *event)
{
   int r;
   snd_seq_event_t *ev;
   alsa_midi_t *d = (alsa_midi_t*)p;

   r = snd_seq_event_input(d->seq, &ev);
   if (r < 0)
   {
#ifdef DEBUG
      if (r != -EAGAIN)
         RARCH_ERR("[MIDI]: snd_seq_event_input failed with error %d.\n", r);
#endif
      return false;
   }

   if (ev->type == SND_SEQ_EVENT_NOTEOFF)
   {
      event->data[0]   = 0x80 | ev->data.note.channel;
      event->data[1]   = ev->data.note.note;
      event->data[2]   = ev->data.note.velocity;
      event->data_size = 3;
   }
   else if (ev->type == SND_SEQ_EVENT_NOTEON)
   {
      event->data[0]   = 0x90 | ev->data.note.channel;
      event->data[1]   = ev->data.note.note;
      event->data[2]   = ev->data.note.velocity;
      event->data_size = 3;
   }
   else if (ev->type == SND_SEQ_EVENT_KEYPRESS)
   {
      event->data[0]   = 0xA0 | ev->data.note.channel;
      event->data[1]   = ev->data.note.note;
      event->data[2]   = ev->data.note.velocity;
      event->data_size = 3;
   }
   else if (ev->type == SND_SEQ_EVENT_CONTROLLER)
   {
      event->data[0]   = 0xB0 | ev->data.control.channel;
      event->data[1]   = ev->data.control.param;
      event->data[2]   = ev->data.control.value;
      event->data_size = 3;
   }
   else if (ev->type == SND_SEQ_EVENT_PGMCHANGE)
   {
      event->data[0]   = 0xC0 | ev->data.control.channel;
      event->data[1]   = ev->data.control.value;
      event->data_size = 2;
   }
   else if (ev->type == SND_SEQ_EVENT_CHANPRESS)
   {
      event->data[0]   = 0xD0 | ev->data.control.channel;
      event->data[1]   = ev->data.control.value;
      event->data_size = 2;
   }
   else if (ev->type == SND_SEQ_EVENT_PITCHBEND)
   {
      event->data[0]   = 0xE0 | ev->data.control.channel;
      event->data[1]   = ev->data.control.value & 127;
      event->data[2]   = ev->data.control.value >> 7;
      event->data_size = 3;
   }
   else if (ev->type == SND_SEQ_EVENT_SYSEX)
   {
      if (ev->data.ext.len <= event->data_size)
      {
         size_t i;
         uint8_t *ev_data = (uint8_t*)ev->data.ext.ptr;

         for (i = 0; i < ev->data.ext.len; ++i)
            event->data[i] = ev_data[i];

         event->data_size = ev->data.ext.len;
      }
#ifdef DEBUG
      else
      {
         RARCH_ERR("[MIDI]: SysEx event too big.\n");
         r = -1;
      }
#endif
   }
   else
      r = -1;

   event->delta_time = 0;
   snd_seq_free_event(ev);

   return r >= 0;
}