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
typedef  int /*<<< orphan*/  u_char ;
struct nand_chip {scalar_t__ IO_ADDR_W; scalar_t__ IO_ADDR_R; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 int CS_NAND_CTLR_BUSY ; 
 scalar_t__ MM_NAND_STS ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cs553x_write_byte(struct mtd_info *mtd, u_char byte)
{
	struct nand_chip *this = mtd->priv;
	int i = 100000;

	while (i && readb(this->IO_ADDR_R + MM_NAND_STS) & CS_NAND_CTLR_BUSY) {
		udelay(1);
		i--;
	}
	writeb(byte, this->IO_ADDR_W + 0x801);
}