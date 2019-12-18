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
struct TYPE_2__ {size_t written; } ;
typedef  TYPE_1__ ax_audio_t ;

/* Variables and functions */
 size_t AX_AUDIO_COUNT ; 
 size_t AX_AUDIO_SAMPLE_COUNT ; 

__attribute__((used)) static size_t ax_audio_write_avail(void* data)
{
   ax_audio_t* ax = (ax_audio_t*)data;

   size_t ret = AX_AUDIO_COUNT - ax->written;

   return (ret < AX_AUDIO_SAMPLE_COUNT ? 0 : ret);
}