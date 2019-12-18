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
typedef  int /*<<< orphan*/  u64 ;
struct hipz_query_hca {int /*<<< orphan*/  node_guid; } ;
struct TYPE_2__ {int /*<<< orphan*/  node_guid; } ;
struct ehca_shca {TYPE_1__ ib_device; int /*<<< orphan*/  ipz_hca_handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ H_SUCCESS ; 
 struct hipz_query_hca* ehca_alloc_fw_ctrlblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehca_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ehca_free_fw_ctrlblock (struct hipz_query_hca*) ; 
 scalar_t__ hipz_h_query_hca (int /*<<< orphan*/ ,struct hipz_query_hca*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int init_node_guid(struct ehca_shca *shca)
{
	int ret = 0;
	struct hipz_query_hca *rblock;

	rblock = ehca_alloc_fw_ctrlblock(GFP_KERNEL);
	if (!rblock) {
		ehca_err(&shca->ib_device, "Can't allocate rblock memory.");
		return -ENOMEM;
	}

	if (hipz_h_query_hca(shca->ipz_hca_handle, rblock) != H_SUCCESS) {
		ehca_err(&shca->ib_device, "Can't query device properties");
		ret = -EINVAL;
		goto init_node_guid1;
	}

	memcpy(&shca->ib_device.node_guid, &rblock->node_guid, sizeof(u64));

init_node_guid1:
	ehca_free_fw_ctrlblock(rblock);
	return ret;
}