#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct sh_flctl {scalar_t__* hwecc_cant_correct; } ;
struct TYPE_3__ {int size; int bytes; int steps; } ;
struct nand_chip {int /*<<< orphan*/  (* read_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int) ;TYPE_1__ ecc; } ;
struct TYPE_4__ {int /*<<< orphan*/  corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {TYPE_2__ ecc_stats; } ;

/* Variables and functions */
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int flctl_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *p = buf;
	struct sh_flctl *flctl = mtd_to_flctl(mtd);

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
		chip->read_buf(mtd, p, eccsize);

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		if (flctl->hwecc_cant_correct[i])
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += 0;
	}

	return 0;
}