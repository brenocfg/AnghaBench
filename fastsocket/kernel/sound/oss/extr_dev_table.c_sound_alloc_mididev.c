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
 int num_midis ; 
 int /*<<< orphan*/  oss_sound_fops ; 
 int register_sound_midi (int /*<<< orphan*/ *,int) ; 

int sound_alloc_mididev(void)
{
	int i = register_sound_midi(&oss_sound_fops, -1);
	if(i==-1)
		return i;
	i>>=4;
	if(i>=num_midis)
		num_midis = i + 1;
	return i;
}