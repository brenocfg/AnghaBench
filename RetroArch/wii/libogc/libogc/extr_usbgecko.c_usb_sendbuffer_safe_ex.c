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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_Unlock (scalar_t__) ; 
 scalar_t__ __usb_checksend (scalar_t__) ; 
 scalar_t__ __usb_sendbyte (scalar_t__,char) ; 
 int /*<<< orphan*/  __usbgecko_exi_wait (scalar_t__) ; 

int usb_sendbuffer_safe_ex(s32 chn,const void *buffer,int size, int retries)
{
	s32 ret;
	s32 left = size;
	char *ptr = (char*)buffer;

	__usbgecko_exi_wait(chn);
	while(left>0) {
		if(__usb_checksend(chn)) {
			ret = __usb_sendbyte(chn,*ptr);
			if(ret==0) break;

			ptr++;
			left--;
		}

		if (retries >= 0) {
			retries--;
			if (retries == 0)
				break;
		}
	}
	EXI_Unlock(chn);

	return (size - left);
}