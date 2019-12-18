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
struct TYPE_2__ {size_t pos; int /*<<< orphan*/  channel; } ;
typedef  TYPE_1__ ctr_dsp_audio_t ;

/* Variables and functions */
 size_t CTR_DSP_AUDIO_COUNT_MASK ; 
 size_t ndspChnGetSamplePos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ctr_dsp_audio_write_avail(void *data)
{
   ctr_dsp_audio_t* ctr = (ctr_dsp_audio_t*)data;

   return (ndspChnGetSamplePos(ctr->channel) - ctr->pos) & CTR_DSP_AUDIO_COUNT_MASK;
}