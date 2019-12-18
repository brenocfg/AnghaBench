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
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 int /*<<< orphan*/  EXI_Lock (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_Unlock (scalar_t__) ; 
 scalar_t__ __usb_checkrecv (scalar_t__) ; 
 scalar_t__ __usb_recvbyte (scalar_t__,char*) ; 

__attribute__((used)) static int __usb_recvbuffer(s32 chn,void *buffer,int size)
{
	s32 ret;
	s32 left = size;
	char *ptr = (char*)buffer;

	if(!EXI_Lock(chn,EXI_DEVICE_0,NULL)) return 0;

	while(left>0) {
		if(__usb_checkrecv(chn)) {
			ret = __usb_recvbyte(chn,ptr);
			if(ret==0) break;

			ptr++;
			left--;
		}
	}

	EXI_Unlock(chn);
	return (size - left);
}