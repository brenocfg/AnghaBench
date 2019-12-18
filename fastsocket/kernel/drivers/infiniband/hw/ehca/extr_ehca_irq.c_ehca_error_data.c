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
typedef  int /*<<< orphan*/  u64 ;
struct ehca_shca {int /*<<< orphan*/  ib_device; int /*<<< orphan*/  ipz_hca_handle; } ;

/* Variables and functions */
 int EHCA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EHCA_PAGESIZE ; 
 unsigned long ENOMEM ; 
 int /*<<< orphan*/  ERROR_DATA_LENGTH ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long H_R_STATE ; 
 unsigned long H_SUCCESS ; 
 int /*<<< orphan*/ * ehca_alloc_fw_ctrlblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ehca_free_fw_ctrlblock (int /*<<< orphan*/ *) ; 
 unsigned long hipz_h_error_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  print_error_data (struct ehca_shca*,void*,int /*<<< orphan*/ *,int) ; 

int ehca_error_data(struct ehca_shca *shca, void *data,
		    u64 resource)
{

	unsigned long ret;
	u64 *rblock;
	unsigned long block_count;

	rblock = ehca_alloc_fw_ctrlblock(GFP_ATOMIC);
	if (!rblock) {
		ehca_err(&shca->ib_device, "Cannot allocate rblock memory.");
		ret = -ENOMEM;
		goto error_data1;
	}

	/* rblock must be 4K aligned and should be 4K large */
	ret = hipz_h_error_data(shca->ipz_hca_handle,
				resource,
				rblock,
				&block_count);

	if (ret == H_R_STATE)
		ehca_err(&shca->ib_device,
			 "No error data is available: %llx.", resource);
	else if (ret == H_SUCCESS) {
		int length;

		length = EHCA_BMASK_GET(ERROR_DATA_LENGTH, rblock[0]);

		if (length > EHCA_PAGESIZE)
			length = EHCA_PAGESIZE;

		print_error_data(shca, data, rblock, length);
	} else
		ehca_err(&shca->ib_device,
			 "Error data could not be fetched: %llx", resource);

	ehca_free_fw_ctrlblock(rblock);

error_data1:
	return ret;

}