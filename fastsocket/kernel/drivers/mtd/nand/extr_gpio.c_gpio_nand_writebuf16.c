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
struct nand_chip {int /*<<< orphan*/  IO_ADDR_W; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 scalar_t__ IS_ALIGNED (unsigned long,int) ; 
 int /*<<< orphan*/  writesw (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  writew (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_nand_writebuf16(struct mtd_info *mtd, const u_char *buf,
				 int len)
{
	struct nand_chip *this = mtd->priv;

	if (IS_ALIGNED((unsigned long)buf, 2)) {
		writesw(this->IO_ADDR_W, buf, len>>1);
	} else {
		int i;
		unsigned short *ptr = (unsigned short *)buf;

		for (i = 0; i < len; i += 2, ptr++)
			writew(*ptr, this->IO_ADDR_W);
	}
}