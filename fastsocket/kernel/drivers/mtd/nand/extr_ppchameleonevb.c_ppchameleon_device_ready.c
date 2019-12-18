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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPIO0_IR ; 
 int NAND_RB_GPIO_PIN ; 
 int in_be32 (unsigned int volatile*) ; 

__attribute__((used)) static int ppchameleon_device_ready(struct mtd_info *minfo)
{
	if (in_be32((volatile unsigned *)GPIO0_IR) & NAND_RB_GPIO_PIN)
		return 1;
	return 0;
}