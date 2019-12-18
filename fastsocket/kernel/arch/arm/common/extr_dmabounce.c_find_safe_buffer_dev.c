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
struct safe_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmabounce; } ;
struct device {TYPE_1__ archdata; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 struct safe_buffer* find_safe_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static struct safe_buffer *find_safe_buffer_dev(struct device *dev,
		dma_addr_t dma_addr, const char *where)
{
	if (!dev || !dev->archdata.dmabounce)
		return NULL;
	if (dma_mapping_error(dev, dma_addr)) {
		if (dev)
			dev_err(dev, "Trying to %s invalid mapping\n", where);
		else
			pr_err("unknown device: Trying to %s invalid mapping\n", where);
		return NULL;
	}
	return find_safe_buffer(dev->archdata.dmabounce, dma_addr);
}