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
struct TYPE_3__ {struct TYPE_3__* buffer_chunk; struct TYPE_3__* buffer; int /*<<< orphan*/ * pcm; } ;
typedef  TYPE_1__ alsa_qsa_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_pcm_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alsa_qsa_free(void *data)
{
   alsa_qsa_t *alsa = (alsa_qsa_t*)data;

   if (alsa)
   {
      if (alsa->pcm)
      {
         snd_pcm_close(alsa->pcm);
         alsa->pcm = NULL;
      }
      free(alsa->buffer);
      free(alsa->buffer_chunk);
      free(alsa);
   }
}