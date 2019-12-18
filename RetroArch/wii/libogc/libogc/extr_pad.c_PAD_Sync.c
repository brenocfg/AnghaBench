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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ SI_Busy () ; 
 int /*<<< orphan*/  __pad_resettingbits ; 
 int __pad_resettingchan ; 

u32 PAD_Sync()
{
	u32 ret = 0;

	if(!__pad_resettingbits && __pad_resettingchan==32) {
		if(SI_Busy()==0) ret = 1;
	}
	return ret;
}