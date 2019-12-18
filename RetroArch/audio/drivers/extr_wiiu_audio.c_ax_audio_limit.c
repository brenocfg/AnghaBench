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
 int AX_AUDIO_COUNT ; 

__attribute__((used)) static int ax_audio_limit(int in)
{
	if(in < 0)
		in += AX_AUDIO_COUNT;
	else if(in >= AX_AUDIO_COUNT)
		in -= AX_AUDIO_COUNT;
	return in;
}