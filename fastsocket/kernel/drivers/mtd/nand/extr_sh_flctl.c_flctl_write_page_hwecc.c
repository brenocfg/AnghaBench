#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int size; int bytes; int steps; } ;
struct nand_chip {int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,int /*<<< orphan*/  const*,int) ;TYPE_1__ ecc; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void flctl_write_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				   const uint8_t *buf)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	const uint8_t *p = buf;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
		chip->write_buf(mtd, p, eccsize);
}