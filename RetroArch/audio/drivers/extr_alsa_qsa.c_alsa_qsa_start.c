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
struct TYPE_2__ {int is_paused; int /*<<< orphan*/  pcm; scalar_t__ can_pause; } ;
typedef  TYPE_1__ alsa_qsa_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ) ; 
 int snd_pcm_playback_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 

__attribute__((used)) static bool alsa_qsa_start(void *data, bool is_shutdown)
{
   alsa_qsa_t *alsa = (alsa_qsa_t*)data;

   if (alsa->can_pause && alsa->is_paused)
   {
      int ret = snd_pcm_playback_resume(alsa->pcm);

      if (ret < 0)
      {
         RARCH_ERR("[ALSA QSA]: Failed to unpause: %s.\n",
               snd_strerror(ret));
         return false;
      }

      alsa->is_paused = false;
   }

   return true;
}