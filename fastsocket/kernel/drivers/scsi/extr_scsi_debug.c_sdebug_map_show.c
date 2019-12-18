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
struct device_driver {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_scnlistprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_size ; 
 int /*<<< orphan*/  map_storep ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_debug_lbp () ; 
 int /*<<< orphan*/  sdebug_store_sectors ; 

__attribute__((used)) static ssize_t sdebug_map_show(struct device_driver *ddp, char *buf)
{
	ssize_t count;

	if (!scsi_debug_lbp())
		return scnprintf(buf, PAGE_SIZE, "0-%u\n",
				 sdebug_store_sectors);

	count = bitmap_scnlistprintf(buf, PAGE_SIZE, map_storep, map_size);

	buf[count++] = '\n';
	buf[count++] = 0;

	return count;
}