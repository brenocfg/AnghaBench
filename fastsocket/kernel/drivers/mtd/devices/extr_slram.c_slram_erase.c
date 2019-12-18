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
struct mtd_info {scalar_t__ size; TYPE_1__* priv; } ;
struct erase_info {scalar_t__ addr; scalar_t__ len; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {scalar_t__ start; } ;
typedef  TYPE_1__ slram_priv_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MTD_ERASE_DONE ; 
 int /*<<< orphan*/  memset (scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  mtd_erase_callback (struct erase_info*) ; 

__attribute__((used)) static int slram_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	slram_priv_t *priv = mtd->priv;

	if (instr->addr + instr->len > mtd->size) {
		return(-EINVAL);
	}

	memset(priv->start + instr->addr, 0xff, instr->len);

	/* This'll catch a few races. Free the thing before returning :)
	 * I don't feel at all ashamed. This kind of thing is possible anyway
	 * with flash, but unlikely.
	 */

	instr->state = MTD_ERASE_DONE;

	mtd_erase_callback(instr);

	return(0);
}