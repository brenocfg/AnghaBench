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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int EBUSY ; 
 struct resource* __request_region (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 

int __check_region(struct resource *parent, resource_size_t start,
			resource_size_t n)
{
	struct resource * res;

	res = __request_region(parent, start, n, "check-region", 0);
	if (!res)
		return -EBUSY;

	release_resource(res);
	kfree(res);
	return 0;
}