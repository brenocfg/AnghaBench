#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_smart_log {int* temperature; } ;
struct nvme_ns {struct nvme_dev* dev; } ;
struct nvme_dev {TYPE_2__* pci_dev; } ;
struct TYPE_3__ {void** cdw10; int /*<<< orphan*/  prp1; void* nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  c ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BYTES_TO_DWORDS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KELVIN_TEMP_FACTOR ; 
 int LOG_PAGE_TEMPERATURE_PAGE ; 
 int /*<<< orphan*/  LOG_TEMP_PAGE_LENGTH ; 
 int LOG_TEMP_UNKNOWN ; 
 int /*<<< orphan*/  NVME_FEAT_TEMP_THRESH ; 
 int NVME_GET_SMART_LOG_PAGE ; 
 int NVME_SC_SUCCESS ; 
 int REMAINING_TEMP_PAGE_LENGTH ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_admin_get_log_page ; 
 int nvme_get_features (struct nvme_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int nvme_submit_admin_cmd (struct nvme_dev*,struct nvme_command*,int /*<<< orphan*/ *) ; 
 int nvme_trans_copy_to_user (struct sg_io_hdr*,int*,int) ; 

__attribute__((used)) static int nvme_trans_log_temperature(struct nvme_ns *ns, struct sg_io_hdr *hdr,
					int alloc_len)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	int xfer_len;
	u8 *log_response;
	struct nvme_command c;
	struct nvme_dev *dev = ns->dev;
	struct nvme_smart_log *smart_log;
	dma_addr_t dma_addr;
	void *mem;
	u32 feature_resp;
	u8 temp_c_cur, temp_c_thresh;
	u16 temp_k;

	log_response = kzalloc(LOG_TEMP_PAGE_LENGTH, GFP_KERNEL);
	if (log_response == NULL) {
		res = -ENOMEM;
		goto out_mem;
	}

	mem = dma_alloc_coherent(&dev->pci_dev->dev,
					sizeof(struct nvme_smart_log),
					&dma_addr, GFP_KERNEL);
	if (mem == NULL) {
		res = -ENOMEM;
		goto out_dma;
	}

	/* Get SMART Log Page */
	memset(&c, 0, sizeof(c));
	c.common.opcode = nvme_admin_get_log_page;
	c.common.nsid = cpu_to_le32(0xFFFFFFFF);
	c.common.prp1 = cpu_to_le64(dma_addr);
	c.common.cdw10[0] = cpu_to_le32(((sizeof(struct nvme_smart_log) /
			BYTES_TO_DWORDS) << 16) | NVME_GET_SMART_LOG_PAGE);
	res = nvme_submit_admin_cmd(dev, &c, NULL);
	if (res != NVME_SC_SUCCESS) {
		temp_c_cur = LOG_TEMP_UNKNOWN;
	} else {
		smart_log = mem;
		temp_k = (smart_log->temperature[1] << 8) +
				(smart_log->temperature[0]);
		temp_c_cur = temp_k - KELVIN_TEMP_FACTOR;
	}

	/* Get Features for Temp Threshold */
	res = nvme_get_features(dev, NVME_FEAT_TEMP_THRESH, 0, 0,
								&feature_resp);
	if (res != NVME_SC_SUCCESS)
		temp_c_thresh = LOG_TEMP_UNKNOWN;
	else
		temp_c_thresh = (feature_resp & 0xFFFF) - KELVIN_TEMP_FACTOR;

	log_response[0] = LOG_PAGE_TEMPERATURE_PAGE;
	/* Subpage=0x00, Page Length MSB=0 */
	log_response[3] = REMAINING_TEMP_PAGE_LENGTH;
	/* Temperature Log Parameter 1 (Temperature) Start */
	/* Parameter Code = 0x0000 */
	log_response[6] = 0x01;		/* Format and Linking = 01b */
	log_response[7] = 0x02;		/* Parameter Length */
	/* Use Temperature from NVMe Get Log Page, convert to C from K */
	log_response[9] = temp_c_cur;
	/* Temperature Log Parameter 2 (Reference Temperature) Start */
	log_response[11] = 0x01;	/* Parameter Code = 0x0001 */
	log_response[12] = 0x01;	/* Format and Linking = 01b */
	log_response[13] = 0x02;	/* Parameter Length */
	/* Use Temperature Thresh from NVMe Get Log Page, convert to C from K */
	log_response[15] = temp_c_thresh;

	xfer_len = min(alloc_len, LOG_TEMP_PAGE_LENGTH);
	res = nvme_trans_copy_to_user(hdr, log_response, xfer_len);

	dma_free_coherent(&dev->pci_dev->dev, sizeof(struct nvme_smart_log),
			  mem, dma_addr);
 out_dma:
	kfree(log_response);
 out_mem:
	return res;
}