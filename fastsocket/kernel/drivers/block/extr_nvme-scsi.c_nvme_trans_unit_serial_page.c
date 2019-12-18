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
typedef  int /*<<< orphan*/  u8 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {struct nvme_dev* dev; } ;
struct nvme_dev {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  INQ_SERIAL_NUMBER_LENGTH ; 
 int /*<<< orphan*/  INQ_UNIT_SERIAL_NUMBER_PAGE ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int /*<<< orphan*/  STANDARD_INQUIRY_LENGTH ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int nvme_trans_copy_to_user (struct sg_io_hdr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_trans_unit_serial_page(struct nvme_ns *ns,
					struct sg_io_hdr *hdr, u8 *inq_response,
					int alloc_len)
{
	struct nvme_dev *dev = ns->dev;
	int res = SNTI_TRANSLATION_SUCCESS;
	int xfer_len;

	memset(inq_response, 0, STANDARD_INQUIRY_LENGTH);
	inq_response[1] = INQ_UNIT_SERIAL_NUMBER_PAGE; /* Page Code */
	inq_response[3] = INQ_SERIAL_NUMBER_LENGTH;    /* Page Length */
	strncpy(&inq_response[4], dev->serial, INQ_SERIAL_NUMBER_LENGTH);

	xfer_len = min(alloc_len, STANDARD_INQUIRY_LENGTH);
	res = nvme_trans_copy_to_user(hdr, inq_response, xfer_len);

	return res;
}