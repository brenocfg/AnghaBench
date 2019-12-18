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
struct fsg_dev {int /*<<< orphan*/  ref; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct fsg_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fsg_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lun_release(struct device *dev)
{
	struct fsg_dev	*fsg = dev_get_drvdata(dev);

	kref_put(&fsg->ref, fsg_release);
}