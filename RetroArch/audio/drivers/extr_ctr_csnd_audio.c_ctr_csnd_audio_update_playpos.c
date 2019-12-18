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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int cpu_ticks_last; int playpos; } ;
typedef  TYPE_1__ ctr_csnd_audio_t ;

/* Variables and functions */
 int CTR_CSND_AUDIO_COUNT_MASK ; 
 int CTR_CSND_CPU_TICKS_PER_SAMPLE ; 
 int svcGetSystemTick () ; 

__attribute__((used)) static void ctr_csnd_audio_update_playpos(ctr_csnd_audio_t* ctr)
{
   uint64_t current_tick   = svcGetSystemTick();
   uint32_t samples_played = (current_tick - ctr->cpu_ticks_last)
      / CTR_CSND_CPU_TICKS_PER_SAMPLE;

   ctr->playpos   = (ctr->playpos + samples_played) & CTR_CSND_AUDIO_COUNT_MASK;
   ctr->cpu_ticks_last += samples_played * CTR_CSND_CPU_TICKS_PER_SAMPLE;
}