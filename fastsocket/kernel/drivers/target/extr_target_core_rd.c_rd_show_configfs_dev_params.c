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
struct se_device {int dummy; } ;
struct rd_dev {int rd_dev_id; int rd_page_count; int /*<<< orphan*/  sg_table_count; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 struct rd_dev* RD_DEV (struct se_device*) ; 
 int sprintf (char*,char*,int,...) ; 

__attribute__((used)) static ssize_t rd_show_configfs_dev_params(struct se_device *dev, char *b)
{
	struct rd_dev *rd_dev = RD_DEV(dev);

	ssize_t bl = sprintf(b, "TCM RamDisk ID: %u  RamDisk Makeup: rd_mcp\n",
			rd_dev->rd_dev_id);
	bl += sprintf(b + bl, "        PAGES/PAGE_SIZE: %u*%lu"
			"  SG_table_count: %u\n", rd_dev->rd_page_count,
			PAGE_SIZE, rd_dev->sg_table_count);
	return bl;
}