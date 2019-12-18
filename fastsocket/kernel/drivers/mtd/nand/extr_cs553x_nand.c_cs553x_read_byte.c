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
struct nand_chip {int /*<<< orphan*/  IO_ADDR_R; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 unsigned char readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char cs553x_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *this = mtd->priv;
	return readb(this->IO_ADDR_R);
}