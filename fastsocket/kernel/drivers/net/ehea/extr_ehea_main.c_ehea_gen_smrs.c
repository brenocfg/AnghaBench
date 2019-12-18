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
struct ehea_port_res {int /*<<< orphan*/  send_mr; int /*<<< orphan*/  recv_mr; TYPE_1__* port; } ;
struct ehea_adapter {int /*<<< orphan*/  mr; } ;
struct TYPE_2__ {struct ehea_adapter* adapter; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ehea_error (char*) ; 
 int ehea_gen_smr (struct ehea_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehea_rem_mr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehea_gen_smrs(struct ehea_port_res *pr)
{
	int ret;
	struct ehea_adapter *adapter = pr->port->adapter;

	ret = ehea_gen_smr(adapter, &adapter->mr, &pr->send_mr);
	if (ret)
		goto out;

	ret = ehea_gen_smr(adapter, &adapter->mr, &pr->recv_mr);
	if (ret)
		goto out_free;

	return 0;

out_free:
	ehea_rem_mr(&pr->send_mr);
out:
	ehea_error("Generating SMRS failed\n");
	return -EIO;
}