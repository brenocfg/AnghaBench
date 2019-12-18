#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct TYPE_4__ {int port; int /*<<< orphan*/  client; } ;
struct TYPE_5__ {int out_queue; int /*<<< orphan*/  seq; TYPE_3__ out; TYPE_1__ out_src; } ;
typedef  TYPE_2__ alsa_midi_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,int) ; 
 int SND_SEQ_PORT_CAP_READ ; 
 int SND_SEQ_PORT_CAP_SUBS_READ ; 
 int SND_SEQ_PORT_CAP_SUBS_WRITE ; 
 int SND_SEQ_PORT_CAP_WRITE ; 
 int /*<<< orphan*/  SND_SEQ_PORT_TYPE_APPLICATION ; 
 int /*<<< orphan*/  alsa_midi_get_port (int /*<<< orphan*/ ,char const*,int,TYPE_3__*) ; 
 int snd_seq_alloc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_client_id (int /*<<< orphan*/ ) ; 
 int snd_seq_connect_to (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_seq_create_simple_port (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_delete_simple_port (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_seq_free_queue (int /*<<< orphan*/ ,int) ; 
 int snd_seq_start_queue (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_stop_queue (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool alsa_midi_set_output(void *p, const char *output)
{
   int r;
   alsa_midi_t *d = (alsa_midi_t*)p;

   if (!output)
   {
      if (d->out_queue >= 0)
      {
         snd_seq_stop_queue(d->seq, d->out_queue, NULL);
         snd_seq_free_queue(d->seq, d->out_queue);
         d->out_queue = -1;
      }
      if (d->out_src.port >= 0)
      {
         snd_seq_delete_simple_port(d->seq, d->out_src.port);
         d->out_src.port = -1;
      }

      return true;
   }

   if (!alsa_midi_get_port(d->seq, output, SND_SEQ_PORT_CAP_WRITE |
         SND_SEQ_PORT_CAP_SUBS_WRITE, &d->out))
      return false;

   r = snd_seq_create_simple_port(d->seq, "out", SND_SEQ_PORT_CAP_READ |
         SND_SEQ_PORT_CAP_SUBS_READ, SND_SEQ_PORT_TYPE_APPLICATION);
   if (r < 0)
   {
      RARCH_ERR("[MIDI]: snd_seq_create_simple_port failed with error %d.\n", r);
      return false;
   }

   d->out_src.client = snd_seq_client_id(d->seq);
   d->out_src.port   = r;

   r = snd_seq_connect_to(d->seq, d->out_src.port, d->out.client, d->out.port);
   if (r < 0)
   {
      RARCH_ERR("[MIDI]: snd_seq_connect_to failed with error %d.\n", r);
      return false;
   }

   d->out_queue = snd_seq_alloc_queue(d->seq);
   if (d->out_queue < 0)
   {
      RARCH_ERR("[MIDI]: snd_seq_alloc_queue failed with error %d.\n", d->out_queue);
      return false;
   }

   r = snd_seq_start_queue(d->seq, d->out_queue, NULL);
   if (r < 0)
   {
       RARCH_ERR("[MIDI]: snd_seq_start_queue failed with error %d.\n", r);
       return false;
   }

   return true;
}