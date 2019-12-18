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
typedef  TYPE_1__ alsa_t ;

/* Variables and functions */
 int snd_pcm_pause (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool alsa_stop(void *data)
{
   alsa_t *alsa = (alsa_t*)data;
   if (alsa->is_paused)
	  return true;

   if (alsa->can_pause
         && !alsa->is_paused)
   {
      int ret = snd_pcm_pause(alsa->pcm, 1);

      if (ret < 0)
         return false;

      alsa->is_paused = true;
   }

   return true;
}