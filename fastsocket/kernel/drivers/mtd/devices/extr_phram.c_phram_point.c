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
struct mtd_info {scalar_t__ size; void* priv; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int phram_point(struct mtd_info *mtd, loff_t from, size_t len,
		size_t *retlen, void **virt, resource_size_t *phys)
{
	if (from + len > mtd->size)
		return -EINVAL;

	/* can we return a physical address with this driver? */
	if (phys)
		return -EINVAL;

	*virt = mtd->priv + from;
	*retlen = len;
	return 0;
}