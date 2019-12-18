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
struct onenand_chip {int* diesize; unsigned int* boundary; int erase_shift; unsigned int density_mask; } ;
typedef  int loff_t ;

/* Variables and functions */
 scalar_t__ ONENAND_IS_DDP (struct onenand_chip*) ; 

__attribute__((used)) static unsigned flexonenand_block(struct onenand_chip *this, loff_t addr)
{
	unsigned boundary, blk, die = 0;

	if (ONENAND_IS_DDP(this) && addr >= this->diesize[0]) {
		die = 1;
		addr -= this->diesize[0];
	}

	boundary = this->boundary[die];

	blk = addr >> (this->erase_shift - 1);
	if (blk > boundary)
		blk = (blk + boundary + 1) >> 1;

	blk += die ? this->density_mask : 0;
	return blk;
}