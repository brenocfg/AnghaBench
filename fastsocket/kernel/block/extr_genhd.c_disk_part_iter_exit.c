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
struct disk_part_iter {int /*<<< orphan*/ * part; } ;

/* Variables and functions */
 int /*<<< orphan*/  disk_put_part (int /*<<< orphan*/ *) ; 

void disk_part_iter_exit(struct disk_part_iter *piter)
{
	disk_put_part(piter->part);
	piter->part = NULL;
}