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
struct mtd_part {scalar_t__ offset; TYPE_1__* master; } ;
struct mtd_info {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* unpoint ) (TYPE_1__*,scalar_t__,size_t) ;} ;

/* Variables and functions */
 struct mtd_part* PART (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__,size_t) ; 

__attribute__((used)) static void part_unpoint(struct mtd_info *mtd, loff_t from, size_t len)
{
	struct mtd_part *part = PART(mtd);

	part->master->unpoint(part->master, from + part->offset, len);
}