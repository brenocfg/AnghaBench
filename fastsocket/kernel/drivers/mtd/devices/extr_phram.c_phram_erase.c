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
struct mtd_info {scalar_t__ size; int /*<<< orphan*/ * priv; } ;
struct erase_info {scalar_t__ addr; scalar_t__ len; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MTD_ERASE_DONE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  mtd_erase_callback (struct erase_info*) ; 

__attribute__((used)) static int phram_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	u_char *start = mtd->priv;

	if (instr->addr + instr->len > mtd->size)
		return -EINVAL;

	memset(start + instr->addr, 0xff, instr->len);

	/* This'll catch a few races. Free the thing before returning :)
	 * I don't feel at all ashamed. This kind of thing is possible anyway
	 * with flash, but unlikely.
	 */

	instr->state = MTD_ERASE_DONE;

	mtd_erase_callback(instr);

	return 0;
}