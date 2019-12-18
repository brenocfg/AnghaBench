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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 unsigned int AUDIO_MIXER_MAX_VOICES ; 
 int /*<<< orphan*/  AUDIO_MIXER_TYPE_NONE ; 
 unsigned int s_rate ; 
 TYPE_1__* s_voices ; 

void audio_mixer_init(unsigned rate)
{
   unsigned i;

   s_rate = rate;

   for (i = 0; i < AUDIO_MIXER_MAX_VOICES; i++)
      s_voices[i].type = AUDIO_MIXER_TYPE_NONE;
}