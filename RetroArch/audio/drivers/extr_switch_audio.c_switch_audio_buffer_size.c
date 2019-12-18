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
 size_t sample_buffer_size ; 
 int switch_audio_data_size () ; 

__attribute__((used)) static size_t switch_audio_buffer_size(void *data)
{
   (void) data;
#ifdef HAVE_LIBNX
   return (switch_audio_data_size() + 0xfff) & ~0xfff;
#else
   return sample_buffer_size;
#endif
}