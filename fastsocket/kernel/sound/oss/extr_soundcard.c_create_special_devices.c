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
 int /*<<< orphan*/  oss_sound_fops ; 
 int register_sound_special (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unregister_sound_special (int) ; 

__attribute__((used)) static int create_special_devices(void)
{
	int seq1,seq2;
	seq1=register_sound_special(&oss_sound_fops, 1);
	if(seq1==-1)
		goto bad;
	seq2=register_sound_special(&oss_sound_fops, 8);
	if(seq2!=-1)
		return 0;
	unregister_sound_special(1);
bad:
	return -1;
}