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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ pages_expand; } ;
struct zram {TYPE_1__ stats; int /*<<< orphan*/  mem_pool; scalar_t__ init_done; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct zram* dev_to_zram (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int xv_get_total_size_bytes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t mem_used_total_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	u64 val = 0;
	struct zram *zram = dev_to_zram(dev);

	if (zram->init_done) {
		val = xv_get_total_size_bytes(zram->mem_pool) +
			((u64)(zram->stats.pages_expand) << PAGE_SHIFT);
	}

	return sprintf(buf, "%llu\n", val);
}