#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  snd_pcm_t ;
typedef  int /*<<< orphan*/  snd_pcm_hw_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  SND_PCM_FORMAT_FLOAT ; 
 scalar_t__ snd_pcm_hw_params_test_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool alsathread_find_float_format(snd_pcm_t *pcm,
      snd_pcm_hw_params_t *params)
{
   if (snd_pcm_hw_params_test_format(pcm, params, SND_PCM_FORMAT_FLOAT) == 0)
   {
      RARCH_LOG("ALSA: Using floating point format.\n");
      return true;
   }
   RARCH_LOG("ALSA: Using signed 16-bit format.\n");
   return false;
}