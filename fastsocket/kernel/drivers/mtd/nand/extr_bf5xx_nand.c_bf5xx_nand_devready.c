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
 unsigned short NBUSYIRQ ; 
 unsigned short bfin_read_NFC_IRQSTAT () ; 

__attribute__((used)) static int bf5xx_nand_devready(struct mtd_info *mtd)
{
	unsigned short val = bfin_read_NFC_IRQSTAT();

	if ((val & NBUSYIRQ) == NBUSYIRQ)
		return 1;
	else
		return 0;
}