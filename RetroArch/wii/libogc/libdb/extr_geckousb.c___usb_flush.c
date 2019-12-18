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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 int /*<<< orphan*/  EXI_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_Unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ __usb_recvbyte (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void __usb_flush(s32 chn)
{
	char tmp;

	if(!EXI_Lock(chn,EXI_DEVICE_0,NULL)) return;

	while(__usb_recvbyte(chn,&tmp));

	EXI_Unlock(chn);
}