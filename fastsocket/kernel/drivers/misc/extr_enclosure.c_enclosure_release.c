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
struct enclosure_device {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct enclosure_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 struct enclosure_device* to_enclosure_device (struct device*) ; 

__attribute__((used)) static void enclosure_release(struct device *cdev)
{
	struct enclosure_device *edev = to_enclosure_device(cdev);

	put_device(cdev->parent);
	kfree(edev);
}