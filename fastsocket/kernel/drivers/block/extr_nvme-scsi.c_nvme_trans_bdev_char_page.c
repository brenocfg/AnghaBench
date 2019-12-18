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
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXTENDED_INQUIRY_DATA_PAGE_LENGTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INQ_BDEV_CHARACTERISTICS_PAGE ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int nvme_trans_copy_to_user (struct sg_io_hdr*,int*,int) ; 

__attribute__((used)) static int nvme_trans_bdev_char_page(struct nvme_ns *ns, struct sg_io_hdr *hdr,
					int alloc_len)
{
	u8 *inq_response;
	int res = SNTI_TRANSLATION_SUCCESS;
	int xfer_len;

	inq_response = kzalloc(EXTENDED_INQUIRY_DATA_PAGE_LENGTH, GFP_KERNEL);
	if (inq_response == NULL) {
		res = -ENOMEM;
		goto out_mem;
	}

	inq_response[1] = INQ_BDEV_CHARACTERISTICS_PAGE;    /* Page Code */
	inq_response[2] = 0x00;    /* Page Length MSB */
	inq_response[3] = 0x3C;    /* Page Length LSB */
	inq_response[4] = 0x00;    /* Medium Rotation Rate MSB */
	inq_response[5] = 0x01;    /* Medium Rotation Rate LSB */
	inq_response[6] = 0x00;    /* Form Factor */

	xfer_len = min(alloc_len, EXTENDED_INQUIRY_DATA_PAGE_LENGTH);
	res = nvme_trans_copy_to_user(hdr, inq_response, xfer_len);

	kfree(inq_response);
 out_mem:
	return res;
}