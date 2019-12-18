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
 int /*<<< orphan*/  __usb_open (int /*<<< orphan*/ *) ; 
 scalar_t__ __usb_register (int /*<<< orphan*/ *) ; 

void physbusif_init()
{
	s32 ret;

	ret = __usb_register(NULL);
	if(ret<0) return;

	__usb_open(NULL);
}