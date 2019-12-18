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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GET_MODE_SENSE_DBD (int*) ; 
 int GET_MODE_SENSE_LLBAA (int*) ; 
 int GET_MODE_SENSE_MPH_SIZE (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int min (scalar_t__,scalar_t__) ; 
 int nvme_trans_copy_to_user (struct sg_io_hdr*,int*,int) ; 
 int nvme_trans_fill_blk_desc (struct nvme_ns*,struct sg_io_hdr*,int*,scalar_t__,int) ; 
 int nvme_trans_fill_mode_parm_hdr (int*,int,int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ nvme_trans_get_blk_desc_len (int,int) ; 

__attribute__((used)) static int nvme_trans_mode_page_create(struct nvme_ns *ns,
					struct sg_io_hdr *hdr, u8 *cmd,
					u16 alloc_len, u8 cdb10,
					int (*mode_page_fill_func)
					(struct nvme_ns *,
					struct sg_io_hdr *hdr, u8 *, int),
					u16 mode_pages_tot_len)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	int xfer_len;
	u8 *response;
	u8 dbd, llbaa;
	u16 resp_size;
	int mph_size;
	u16 mode_pages_offset_1;
	u16 blk_desc_len, blk_desc_offset, mode_data_length;

	dbd = GET_MODE_SENSE_DBD(cmd);
	llbaa = GET_MODE_SENSE_LLBAA(cmd);
	mph_size = GET_MODE_SENSE_MPH_SIZE(cdb10);
	blk_desc_len = nvme_trans_get_blk_desc_len(dbd, llbaa);

	resp_size = mph_size + blk_desc_len + mode_pages_tot_len;
	/* Refer spc4r34 Table 440 for calculation of Mode data Length field */
	mode_data_length = 3 + (3 * cdb10) + blk_desc_len + mode_pages_tot_len;

	blk_desc_offset = mph_size;
	mode_pages_offset_1 = blk_desc_offset + blk_desc_len;

	response = kzalloc(resp_size, GFP_KERNEL);
	if (response == NULL) {
		res = -ENOMEM;
		goto out_mem;
	}

	res = nvme_trans_fill_mode_parm_hdr(&response[0], mph_size, cdb10,
					llbaa, mode_data_length, blk_desc_len);
	if (res != SNTI_TRANSLATION_SUCCESS)
		goto out_free;
	if (blk_desc_len > 0) {
		res = nvme_trans_fill_blk_desc(ns, hdr,
					       &response[blk_desc_offset],
					       blk_desc_len, llbaa);
		if (res != SNTI_TRANSLATION_SUCCESS)
			goto out_free;
	}
	res = mode_page_fill_func(ns, hdr, &response[mode_pages_offset_1],
					mode_pages_tot_len);
	if (res != SNTI_TRANSLATION_SUCCESS)
		goto out_free;

	xfer_len = min(alloc_len, resp_size);
	res = nvme_trans_copy_to_user(hdr, response, xfer_len);

 out_free:
	kfree(response);
 out_mem:
	return res;
}