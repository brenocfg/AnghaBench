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
typedef  scalar_t__ u64 ;
struct hcp_query_ehea {scalar_t__ max_mc_mac; } ;
struct ehea_adapter {scalar_t__ max_mc_mac; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ H_SUCCESS ; 
 scalar_t__ ehea_h_query_ehea (int /*<<< orphan*/ ,struct hcp_query_ehea*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehea_sense_adapter_attr(struct ehea_adapter *adapter)
{
	struct hcp_query_ehea *cb;
	u64 hret;
	int ret;

	cb = (void *)get_zeroed_page(GFP_KERNEL);
	if (!cb) {
		ret = -ENOMEM;
		goto out;
	}

	hret = ehea_h_query_ehea(adapter->handle, cb);

	if (hret != H_SUCCESS) {
		ret = -EIO;
		goto out_herr;
	}

	adapter->max_mc_mac = cb->max_mc_mac - 1;
	ret = 0;

out_herr:
	free_page((unsigned long)cb);
out:
	return ret;
}