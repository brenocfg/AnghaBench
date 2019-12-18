#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  seq; } ;
typedef  TYPE_1__ alsa_midi_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,int) ; 
 int snd_seq_drain_output (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool alsa_midi_flush(void *p)
{
   int r;
   alsa_midi_t *d = (alsa_midi_t*)p;

   r = snd_seq_drain_output(d->seq);
#ifdef DEBUG
   if (r < 0)
      RARCH_ERR("[MIDI]: snd_seq_drain_output failed with error %d.\n", r);
#endif

   return r == 0;
}