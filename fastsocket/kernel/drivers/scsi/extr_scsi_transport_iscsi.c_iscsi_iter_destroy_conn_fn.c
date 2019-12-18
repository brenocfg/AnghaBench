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
 int iscsi_destroy_conn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_dev_to_conn (struct device*) ; 
 int /*<<< orphan*/  iscsi_is_conn_dev (struct device*) ; 

__attribute__((used)) static int iscsi_iter_destroy_conn_fn(struct device *dev, void *data)
{
	if (!iscsi_is_conn_dev(dev))
		return 0;
	return iscsi_destroy_conn(iscsi_dev_to_conn(dev));
}