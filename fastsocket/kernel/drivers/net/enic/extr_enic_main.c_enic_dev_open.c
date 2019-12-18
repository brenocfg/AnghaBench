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
struct enic {int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int enic_dev_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enic_get_dev (struct enic*) ; 
 int /*<<< orphan*/  vnic_dev_open ; 
 int /*<<< orphan*/  vnic_dev_open_done ; 

__attribute__((used)) static int enic_dev_open(struct enic *enic)
{
	int err;

	err = enic_dev_wait(enic->vdev, vnic_dev_open,
		vnic_dev_open_done, 0);
	if (err)
		dev_err(enic_get_dev(enic), "vNIC device open failed, err %d\n",
			err);

	return err;
}