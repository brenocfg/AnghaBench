#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* saved_regs; } ;
typedef  TYPE_1__ ad1848_info ;

/* Variables and functions */
 unsigned char ad_read (TYPE_1__*,int) ; 

__attribute__((used)) static void ad_mute(ad1848_info * devc)
{
	int i;
	unsigned char prev;

	/*
	 * Save old register settings and mute output channels
	 */
	 
	for (i = 6; i < 8; i++)
	{
		prev = devc->saved_regs[i] = ad_read(devc, i);
	}

}