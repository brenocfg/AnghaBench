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
struct mtd_info {int /*<<< orphan*/  erasesize; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NS_ERR (char*) ; 
 int divide (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erase_block_wear ; 
 int /*<<< orphan*/  kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rptwear ; 
 int wear_eb_count ; 

__attribute__((used)) static int setup_wear_reporting(struct mtd_info *mtd)
{
	size_t mem;

	if (!rptwear)
		return 0;
	wear_eb_count = divide(mtd->size, mtd->erasesize);
	mem = wear_eb_count * sizeof(unsigned long);
	if (mem / sizeof(unsigned long) != wear_eb_count) {
		NS_ERR("Too many erase blocks for wear reporting\n");
		return -ENOMEM;
	}
	erase_block_wear = kzalloc(mem, GFP_KERNEL);
	if (!erase_block_wear) {
		NS_ERR("Too many erase blocks for wear reporting\n");
		return -ENOMEM;
	}
	return 0;
}