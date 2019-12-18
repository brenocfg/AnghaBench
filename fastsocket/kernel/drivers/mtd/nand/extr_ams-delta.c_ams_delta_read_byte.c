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
struct nand_chip {int /*<<< orphan*/  IO_ADDR_R; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_DELTA_LATCH2_NAND_NRE ; 
 scalar_t__ OMAP1_MPUIO_BASE ; 
 scalar_t__ OMAP_MPUIO_IO_CNTL ; 
 int /*<<< orphan*/  ams_delta_latch2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u_char ams_delta_read_byte(struct mtd_info *mtd)
{
	u_char res;
	struct nand_chip *this = mtd->priv;

	ams_delta_latch2_write(AMS_DELTA_LATCH2_NAND_NRE, 0);
	ndelay(40);
	omap_writew(~0, (OMAP1_MPUIO_BASE + OMAP_MPUIO_IO_CNTL));
	res = omap_readw(this->IO_ADDR_R);
	ams_delta_latch2_write(AMS_DELTA_LATCH2_NAND_NRE,
			       AMS_DELTA_LATCH2_NAND_NRE);

	return res;
}