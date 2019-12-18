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
struct TYPE_2__ {int nonblock; int /*<<< orphan*/  pcm; } ;
typedef  TYPE_1__ alsa_qsa_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,int,int /*<<< orphan*/ ) ; 
 int snd_pcm_nonblock_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 

__attribute__((used)) static void alsa_qsa_set_nonblock_state(void *data, bool state)
{
   alsa_qsa_t *alsa = (alsa_qsa_t*)data;

   int err;

   if((err = snd_pcm_nonblock_mode(alsa->pcm, state)) < 0)
   {
      RARCH_ERR("Can't set blocking mode to %d: %s\n", state,
            snd_strerror(err));
      return;
   }

   alsa->nonblock = state;
}