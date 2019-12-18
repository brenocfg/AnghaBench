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
 int /*<<< orphan*/  TS72XX_NAND_BUSY_VIRT_BASE ; 
 int __raw_readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts7250_device_ready(struct mtd_info *mtd)
{
	return __raw_readb(TS72XX_NAND_BUSY_VIRT_BASE) & 0x20;
}