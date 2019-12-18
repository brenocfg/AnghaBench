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
struct CHIPSTATE {int dummy; } ;

/* Variables and functions */
 int chip_read2 (struct CHIPSTATE*,int) ; 

__attribute__((used)) static int tda9873_checkit(struct CHIPSTATE *chip)
{
	int rc;

	if (-1 == (rc = chip_read2(chip,254)))
		return 0;
	return (rc & ~0x1f) == 0x80;
}