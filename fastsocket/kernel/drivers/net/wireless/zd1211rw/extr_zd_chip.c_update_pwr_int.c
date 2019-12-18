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
struct zd_chip {int* pwr_int_values; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_CR31 ; 
 int zd_iowrite16_locked (struct zd_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_pwr_int(struct zd_chip *chip, u8 channel)
{
	u8 value = chip->pwr_int_values[channel - 1];
	return zd_iowrite16_locked(chip, value, ZD_CR31);
}