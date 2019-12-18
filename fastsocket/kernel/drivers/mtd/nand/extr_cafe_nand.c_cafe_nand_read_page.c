#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned short uint8_t ;
typedef  int uint32_t ;
typedef  unsigned short u8 ;
struct nand_chip {unsigned short* oob_poi; int /*<<< orphan*/  (* read_buf ) (struct mtd_info*,unsigned short*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {TYPE_2__ ecc_stats; int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; struct cafe_priv* priv; } ;
struct cafe_priv {TYPE_1__* pdev; scalar_t__ mmio; TYPE_3__* rs; } ;
struct TYPE_6__ {unsigned short* index_of; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ NAND_ADDR2 ; 
 scalar_t__ NAND_ECC_RESULT ; 
 scalar_t__ NAND_ECC_SYN01 ; 
 int /*<<< orphan*/  cafe_dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int cafe_readl (struct cafe_priv*,scalar_t__) ; 
 scalar_t__ checkecc ; 
 int decode_rs16 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned short*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,unsigned short*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,unsigned short*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cafe_nand_read_page(struct mtd_info *mtd, struct nand_chip *chip,
			       uint8_t *buf, int page)
{
	struct cafe_priv *cafe = mtd->priv;

	cafe_dev_dbg(&cafe->pdev->dev, "ECC result %08x SYN1,2 %08x\n",
		     cafe_readl(cafe, NAND_ECC_RESULT),
		     cafe_readl(cafe, NAND_ECC_SYN01));

	chip->read_buf(mtd, buf, mtd->writesize);
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);

	if (checkecc && cafe_readl(cafe, NAND_ECC_RESULT) & (1<<18)) {
		unsigned short syn[8], pat[4];
		int pos[4];
		u8 *oob = chip->oob_poi;
		int i, n;

		for (i=0; i<8; i+=2) {
			uint32_t tmp = cafe_readl(cafe, NAND_ECC_SYN01 + (i*2));
			syn[i] = cafe->rs->index_of[tmp & 0xfff];
			syn[i+1] = cafe->rs->index_of[(tmp >> 16) & 0xfff];
		}

		n = decode_rs16(cafe->rs, NULL, NULL, 1367, syn, 0, pos, 0,
		                pat);

		for (i = 0; i < n; i++) {
			int p = pos[i];

			/* The 12-bit symbols are mapped to bytes here */

			if (p > 1374) {
				/* out of range */
				n = -1374;
			} else if (p == 0) {
				/* high four bits do not correspond to data */
				if (pat[i] > 0xff)
					n = -2048;
				else
					buf[0] ^= pat[i];
			} else if (p == 1365) {
				buf[2047] ^= pat[i] >> 4;
				oob[0] ^= pat[i] << 4;
			} else if (p > 1365) {
				if ((p & 1) == 1) {
					oob[3*p/2 - 2048] ^= pat[i] >> 4;
					oob[3*p/2 - 2047] ^= pat[i] << 4;
				} else {
					oob[3*p/2 - 2049] ^= pat[i] >> 8;
					oob[3*p/2 - 2048] ^= pat[i];
				}
			} else if ((p & 1) == 1) {
				buf[3*p/2] ^= pat[i] >> 4;
				buf[3*p/2 + 1] ^= pat[i] << 4;
			} else {
				buf[3*p/2 - 1] ^= pat[i] >> 8;
				buf[3*p/2] ^= pat[i];
			}
		}

		if (n < 0) {
			dev_dbg(&cafe->pdev->dev, "Failed to correct ECC at %08x\n",
				cafe_readl(cafe, NAND_ADDR2) * 2048);
			for (i = 0; i < 0x5c; i += 4)
				printk("Register %x: %08x\n", i, readl(cafe->mmio + i));
			mtd->ecc_stats.failed++;
		} else {
			dev_dbg(&cafe->pdev->dev, "Corrected %d symbol errors\n", n);
			mtd->ecc_stats.corrected += n;
		}
	}

	return 0;
}