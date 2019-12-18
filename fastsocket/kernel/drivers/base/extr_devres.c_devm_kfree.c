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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devm_kzalloc_match ; 
 int /*<<< orphan*/  devm_kzalloc_release ; 
 int devres_destroy (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void devm_kfree(struct device *dev, void *p)
{
	int rc;

	rc = devres_destroy(dev, devm_kzalloc_release, devm_kzalloc_match, p);
	WARN_ON(rc);
}