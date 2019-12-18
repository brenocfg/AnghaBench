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
typedef  int u32 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {struct nvme_dev* dev; } ;
struct nvme_dev {int dummy; } ;

/* Variables and functions */
 int MODE_PAGE_CACHING ; 
 int MODE_PAGE_CACHING_LEN ; 
 int MODE_PAGE_CACHING_LEN_FIELD ; 
 int /*<<< orphan*/  NVME_FEAT_VOLATILE_WC ; 
 int SNTI_INTERNAL_ERROR ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int nvme_get_features (struct nvme_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int nvme_trans_status_code (struct sg_io_hdr*,int) ; 

__attribute__((used)) static int nvme_trans_fill_caching_page(struct nvme_ns *ns,
					struct sg_io_hdr *hdr,
					u8 *resp, int len)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	int nvme_sc;
	struct nvme_dev *dev = ns->dev;
	u32 feature_resp;
	u8 vwc;

	if (len < MODE_PAGE_CACHING_LEN)
		return SNTI_INTERNAL_ERROR;

	nvme_sc = nvme_get_features(dev, NVME_FEAT_VOLATILE_WC, 0, 0,
								&feature_resp);
	res = nvme_trans_status_code(hdr, nvme_sc);
	if (res)
		goto out;
	if (nvme_sc) {
		res = nvme_sc;
		goto out;
	}
	vwc = feature_resp & 0x00000001;

	resp[0] = MODE_PAGE_CACHING;
	resp[1] = MODE_PAGE_CACHING_LEN_FIELD;
	resp[2] = vwc << 2;

 out:
	return res;
}