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
struct TYPE_3__ {scalar_t__ pcm; } ;
typedef  TYPE_1__ alsa_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_config_update_free_global () ; 
 int /*<<< orphan*/  snd_pcm_close (scalar_t__) ; 
 int /*<<< orphan*/  snd_pcm_drop (scalar_t__) ; 

__attribute__((used)) static void alsa_free(void *data)
{
   alsa_t *alsa = (alsa_t*)data;

   if (alsa)
   {
      if (alsa->pcm)
      {
         snd_pcm_drop(alsa->pcm);
         snd_pcm_close(alsa->pcm);
         snd_config_update_free_global();
      }

      free(alsa);
   }
}