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
struct platform_device {int dummy; } ;
struct oxu_info {TYPE_1__** hcd; } ;
struct TYPE_2__ {unsigned long rsrc_start; unsigned long rsrc_len; void* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (struct oxu_info*) ; 
 int /*<<< orphan*/  oxu_remove (struct platform_device*,TYPE_1__*) ; 
 struct oxu_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (unsigned long,unsigned long) ; 

__attribute__((used)) static int oxu_drv_remove(struct platform_device *pdev)
{
	struct oxu_info *info = platform_get_drvdata(pdev);
	unsigned long memstart = info->hcd[0]->rsrc_start,
			memlen = info->hcd[0]->rsrc_len;
	void *base = info->hcd[0]->regs;

	oxu_remove(pdev, info->hcd[0]);
	oxu_remove(pdev, info->hcd[1]);

	iounmap(base);
	release_mem_region(memstart, memlen);

	kfree(info);
	platform_set_drvdata(pdev, NULL);

	return 0;
}