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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_Unlock (int) ; 
 int __flashreadcommand (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __usbgecko_exi_wait (int) ; 

int usb_flashread(s32 chn, u32 offset, void *buffer, size_t length)
{
	s32 ret=1;
	u8 *data = (u8*)buffer;

	__usbgecko_exi_wait(chn);
	while (ret && length--)
		ret = __flashreadcommand(chn, offset++, data++);

	EXI_Unlock(chn);

	return ret;
}