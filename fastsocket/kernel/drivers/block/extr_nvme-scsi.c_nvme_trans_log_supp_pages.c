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
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LOG_PAGE_INFORMATIONAL_EXCEPTIONS_PAGE ; 
 int /*<<< orphan*/  LOG_PAGE_SUPPORTED_LOG_PAGES_LENGTH ; 
 int /*<<< orphan*/  LOG_PAGE_SUPPORTED_LOG_PAGES_PAGE ; 
 int /*<<< orphan*/  LOG_PAGE_TEMPERATURE_PAGE ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int /*<<< orphan*/  SUPPORTED_LOG_PAGES_PAGE_LENGTH ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int nvme_trans_copy_to_user (struct sg_io_hdr*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nvme_trans_log_supp_pages(struct nvme_ns *ns, struct sg_io_hdr *hdr,
					int alloc_len)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	int xfer_len;
	u8 *log_response;

	log_response = kzalloc(LOG_PAGE_SUPPORTED_LOG_PAGES_LENGTH, GFP_KERNEL);
	if (log_response == NULL) {
		res = -ENOMEM;
		goto out_mem;
	}

	log_response[0] = LOG_PAGE_SUPPORTED_LOG_PAGES_PAGE;
	/* Subpage=0x00, Page Length MSB=0 */
	log_response[3] = SUPPORTED_LOG_PAGES_PAGE_LENGTH;
	log_response[4] = LOG_PAGE_SUPPORTED_LOG_PAGES_PAGE;
	log_response[5] = LOG_PAGE_INFORMATIONAL_EXCEPTIONS_PAGE;
	log_response[6] = LOG_PAGE_TEMPERATURE_PAGE;

	xfer_len = min(alloc_len, LOG_PAGE_SUPPORTED_LOG_PAGES_LENGTH);
	res = nvme_trans_copy_to_user(hdr, log_response, xfer_len);

	kfree(log_response);
 out_mem:
	return res;
}