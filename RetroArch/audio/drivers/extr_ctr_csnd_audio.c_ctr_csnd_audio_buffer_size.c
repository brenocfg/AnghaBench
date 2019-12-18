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

/* Variables and functions */
 size_t CTR_CSND_AUDIO_COUNT ; 

__attribute__((used)) static size_t ctr_csnd_audio_buffer_size(void *data)
{
   (void)data;
   return CTR_CSND_AUDIO_COUNT;
}