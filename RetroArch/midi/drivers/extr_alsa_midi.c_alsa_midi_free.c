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
struct TYPE_3__ {scalar_t__ seq; } ;
typedef  TYPE_1__ alsa_midi_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_seq_close (scalar_t__) ; 

__attribute__((used)) static void alsa_midi_free(void *p)
{
   alsa_midi_t *d = (alsa_midi_t*)p;

   if (d)
   {
      if (d->seq)
         snd_seq_close(d->seq);
      free(d);
   }
}