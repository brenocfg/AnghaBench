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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ sonypi_ec_read (int,int*) ; 

__attribute__((used)) static int ec_read16(u8 addr, u16 *value)
{
	u8 val_lb, val_hb;
	if (sonypi_ec_read(addr, &val_lb))
		return -1;
	if (sonypi_ec_read(addr + 1, &val_hb))
		return -1;
	*value = val_lb | (val_hb << 8);
	return 0;
}