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
typedef  int /*<<< orphan*/  fstrm_item_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  item_zone ; 
 int /*<<< orphan*/  kmem_zone_init (int,char*) ; 

int
xfs_filestream_init(void)
{
	item_zone = kmem_zone_init(sizeof(fstrm_item_t), "fstrm_item");
	if (!item_zone)
		return -ENOMEM;

	return 0;
}