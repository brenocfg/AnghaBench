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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 char* FIRMWARE_RT2870 ; 

__attribute__((used)) static char *rt2800usb_get_firmware_name(struct rt2x00_dev *rt2x00dev)
{
	return FIRMWARE_RT2870;
}