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
 char* FIRMWARE_RT2860 ; 
 char* FIRMWARE_RT3290 ; 
 int /*<<< orphan*/  RT3290 ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *rt2800pci_get_firmware_name(struct rt2x00_dev *rt2x00dev)
{
	/*
	 * Chip rt3290 use specific 4KB firmware named rt3290.bin.
	 */
	if (rt2x00_rt(rt2x00dev, RT3290))
		return FIRMWARE_RT3290;
	else
		return FIRMWARE_RT2860;
}