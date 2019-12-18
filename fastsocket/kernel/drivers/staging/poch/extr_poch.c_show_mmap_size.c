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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct channel_info {unsigned long group_count; int /*<<< orphan*/  header_size; int /*<<< orphan*/  group_size; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 struct channel_info* dev_get_drvdata (struct device*) ; 
 unsigned long npages (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,unsigned long) ; 

__attribute__((used)) static ssize_t show_mmap_size(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct channel_info *channel = dev_get_drvdata(dev);
	int len;
	unsigned long mmap_size;
	unsigned long group_pages;
	unsigned long header_pages;
	unsigned long total_group_pages;

	group_pages = npages(channel->group_size);
	header_pages = npages(channel->header_size);
	total_group_pages = group_pages * channel->group_count;

	mmap_size = (header_pages + total_group_pages) * PAGE_SIZE;
	len = sprintf(buf, "%lu\n", mmap_size);
	return len;
}