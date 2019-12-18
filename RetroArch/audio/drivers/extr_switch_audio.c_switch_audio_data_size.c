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
typedef  int const uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int const num_channels ; 
 int const sample_buffer_size ; 
 int const sample_rate ; 

__attribute__((used)) static uint32_t switch_audio_data_size(void)
{
#ifdef HAVE_LIBNX
   static const int framerate = 1000 / 30;
   static const int samplecount = (sample_rate / framerate);
   return (samplecount * num_channels * sizeof(uint16_t));
#else
   return sample_buffer_size;
#endif
}