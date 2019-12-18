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
struct scm_device {scalar_t__ address; } ;
struct sale {scalar_t__ sa; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scm_device* to_scm_dev (struct device*) ; 

__attribute__((used)) static int check_address(struct device *dev, void *data)
{
	struct scm_device *scmdev = to_scm_dev(dev);
	struct sale *sale = data;

	return scmdev->address == sale->sa;
}