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
struct rio_dev {int dummy; } ;
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct resource*) ; 
 int release_resource (struct resource*) ; 

int rio_release_outb_dbell(struct rio_dev *rdev, struct resource *res)
{
	int rc = release_resource(res);

	kfree(res);

	return rc;
}