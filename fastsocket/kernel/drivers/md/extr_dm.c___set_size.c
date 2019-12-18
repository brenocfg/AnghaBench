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
struct mapped_device {TYPE_1__* bdev; int /*<<< orphan*/  disk; } ;
typedef  scalar_t__ sector_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  i_size_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __set_size(struct mapped_device *md, sector_t size)
{
	set_capacity(md->disk, size);

	i_size_write(md->bdev->bd_inode, (loff_t)size << SECTOR_SHIFT);
}