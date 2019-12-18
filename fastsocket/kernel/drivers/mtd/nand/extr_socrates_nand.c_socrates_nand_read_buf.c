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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct socrates_nand_host {int /*<<< orphan*/  io_base; } ;
struct nand_chip {struct socrates_nand_host* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 int FPGA_NAND_CMD_READ ; 
 int FPGA_NAND_DATA_SHIFT ; 
 int FPGA_NAND_ENABLE ; 
 int in_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void socrates_nand_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	int i;
	struct nand_chip *this = mtd->priv;
	struct socrates_nand_host *host = this->priv;
	uint32_t val;

	val = FPGA_NAND_ENABLE | FPGA_NAND_CMD_READ;

	out_be32(host->io_base, val);
	for (i = 0; i < len; i++) {
		buf[i] = (in_be32(host->io_base) >>
				FPGA_NAND_DATA_SHIFT) & 0xff;
	}
}