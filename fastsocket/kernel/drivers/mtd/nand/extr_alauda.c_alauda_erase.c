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
struct mtd_info {int dummy; } ;
struct erase_info {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_ERASE_DONE ; 
 int /*<<< orphan*/  MTD_ERASE_FAILED ; 
 int __alauda_erase (struct mtd_info*,struct erase_info*) ; 
 int /*<<< orphan*/  mtd_erase_callback (struct erase_info*) ; 

__attribute__((used)) static int alauda_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	int err;

	err = __alauda_erase(mtd, instr);
	instr->state = err ? MTD_ERASE_FAILED : MTD_ERASE_DONE;
	mtd_erase_callback(instr);
	return err;
}