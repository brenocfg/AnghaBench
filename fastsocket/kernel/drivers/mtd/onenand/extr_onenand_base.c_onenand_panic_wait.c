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
struct onenand_chip {unsigned int (* read_word ) (scalar_t__) ;scalar_t__ base; } ;
struct mtd_info {struct onenand_chip* priv; } ;

/* Variables and functions */
 unsigned int ONENAND_INT_MASTER ; 
 scalar_t__ ONENAND_REG_INTERRUPT ; 
 unsigned int stub1 (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void onenand_panic_wait(struct mtd_info *mtd)
{
	struct onenand_chip *this = mtd->priv;
	unsigned int interrupt;
	int i;
	
	for (i = 0; i < 2000; i++) {
		interrupt = this->read_word(this->base + ONENAND_REG_INTERRUPT);
		if (interrupt & ONENAND_INT_MASTER)
			break;
		udelay(10);
	}
}