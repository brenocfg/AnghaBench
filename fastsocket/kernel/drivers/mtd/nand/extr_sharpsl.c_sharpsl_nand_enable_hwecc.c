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
struct sharpsl_nand {scalar_t__ io; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ ECCCLRR ; 
 struct sharpsl_nand* mtd_to_sharpsl (struct mtd_info*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sharpsl_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
	struct sharpsl_nand *sharpsl = mtd_to_sharpsl(mtd);
	writeb(0, sharpsl->io + ECCCLRR);
}