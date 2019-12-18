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
struct dbginterface {int /*<<< orphan*/  fhndl; } ;

/* Variables and functions */
 int __usb_sendbuffer (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static int usbwrite(struct dbginterface *device,const void *buffer,int size)
{
	int ret;
	ret = __usb_sendbuffer(device->fhndl,buffer,size);
	return ret;
}