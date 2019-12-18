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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int hdaps_device_init () ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int hdaps_probe(struct platform_device *dev)
{
	int ret;

	ret = hdaps_device_init();
	if (ret)
		return ret;

	pr_info("device successfully initialized\n");
	return 0;
}