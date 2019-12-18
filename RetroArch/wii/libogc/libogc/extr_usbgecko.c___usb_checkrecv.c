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
typedef  int u16 ;
typedef  int s32 ;

/* Variables and functions */
 int __send_command (int,int*) ; 

int __usb_checkrecv(s32 chn)
{
	s32 ret;
	u16 val;

	val = 0xD000;
	ret = __send_command(chn,&val);
	if(ret==1 && !(val&0x0400)) ret = 0;

	return ret;
}