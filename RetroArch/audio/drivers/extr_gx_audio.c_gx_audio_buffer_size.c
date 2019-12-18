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
 size_t BLOCKS ; 
 size_t CHUNK_SIZE ; 

__attribute__((used)) static size_t gx_audio_buffer_size(void *data)
{
   (void)data;
   return BLOCKS * CHUNK_SIZE;
}