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
struct map_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jedec_chip_probe ; 
 struct mtd_info* mtd_do_chip_probe (struct map_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mtd_info *jedec_probe(struct map_info *map)
{
	/*
	 * Just use the generic probe stuff to call our CFI-specific
	 * chip_probe routine in all the possible permutations, etc.
	 */
	return mtd_do_chip_probe(map, &jedec_chip_probe);
}