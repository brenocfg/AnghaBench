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
struct hfs_extent {int /*<<< orphan*/  count; int /*<<< orphan*/  block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_EXTENT ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void hfs_dump_extent(struct hfs_extent *extent)
{
	int i;

	dprint(DBG_EXTENT, "   ");
	for (i = 0; i < 3; i++)
		dprint(DBG_EXTENT, " %u:%u", be16_to_cpu(extent[i].block),
				 be16_to_cpu(extent[i].count));
	dprint(DBG_EXTENT, "\n");
}