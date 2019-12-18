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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_part {scalar_t__ offset; TYPE_1__* master; } ;
struct mtd_info {int flags; scalar_t__ size; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int (* panic_write ) (TYPE_1__*,scalar_t__,size_t,size_t*,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int EROFS ; 
 int MTD_WRITEABLE ; 
 struct mtd_part* PART (struct mtd_info*) ; 
 int stub1 (TYPE_1__*,scalar_t__,size_t,size_t*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int part_panic_write(struct mtd_info *mtd, loff_t to, size_t len,
		size_t *retlen, const u_char *buf)
{
	struct mtd_part *part = PART(mtd);
	if (!(mtd->flags & MTD_WRITEABLE))
		return -EROFS;
	if (to >= mtd->size)
		len = 0;
	else if (to + len > mtd->size)
		len = mtd->size - to;
	return part->master->panic_write(part->master, to + part->offset,
				    len, retlen, buf);
}