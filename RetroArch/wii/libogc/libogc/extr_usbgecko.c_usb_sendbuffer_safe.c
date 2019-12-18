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
 int usb_sendbuffer_safe_ex (int /*<<< orphan*/ ,void const*,int,int) ; 

int usb_sendbuffer_safe(s32 chn,const void *buffer,int size) {
	return usb_sendbuffer_safe_ex(chn, buffer, size, -1);
}