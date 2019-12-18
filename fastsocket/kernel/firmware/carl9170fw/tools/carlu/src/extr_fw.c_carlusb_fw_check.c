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
typedef  int /*<<< orphan*/  uint8_t ;
struct carlu {int tx_stream; int extra_headroom; int rx_stream; void* miniboot_size; void* rx_max; int /*<<< orphan*/  dma_chunks; void* dma_chunk_size; int /*<<< orphan*/  fw; } ;
struct carl9170fw_otus_desc {int /*<<< orphan*/  miniboot_size; int /*<<< orphan*/  feature_set; int /*<<< orphan*/  rx_max_frame_len; int /*<<< orphan*/  tx_descs; int /*<<< orphan*/  tx_frag_len; } ;
struct ar9170_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170FW_DUMMY_FEATURE ; 
 int /*<<< orphan*/  CARL9170FW_MINIBOOT ; 
 int /*<<< orphan*/  CARL9170FW_OTUS_DESC_CUR_VER ; 
 int /*<<< orphan*/  CARL9170FW_USB_DOWN_STREAM ; 
 int /*<<< orphan*/  CARL9170FW_USB_INIT_FIRMWARE ; 
 int /*<<< orphan*/  CARL9170FW_USB_RESP_EP2 ; 
 int /*<<< orphan*/  CARL9170FW_USB_UP_STREAM ; 
 int EINVAL ; 
 int ENODATA ; 
 int EOPNOTSUPP ; 
 scalar_t__ OTUS_MAGIC ; 
 scalar_t__ carl9170fw_supports (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct carl9170fw_otus_desc* carlfw_find_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  err (char*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

int carlusb_fw_check(struct carlu *ar)
{
	struct carl9170fw_otus_desc *otus_desc;

	otus_desc = carlfw_find_desc(ar->fw, (uint8_t *) OTUS_MAGIC,
				     sizeof(*otus_desc),
				     CARL9170FW_OTUS_DESC_CUR_VER);

	if (!otus_desc) {
		err("No valid USB descriptor found.\n");
		return -ENODATA;
	}

	if (!carl9170fw_supports(otus_desc->feature_set, CARL9170FW_DUMMY_FEATURE)) {
		err("Invalid Firmware Descriptor.\n");
		return -EINVAL;
	}

	if (!carl9170fw_supports(otus_desc->feature_set, CARL9170FW_USB_INIT_FIRMWARE)) {
		err("Firmware does not know how to initialize USB core.\n");
		return -EOPNOTSUPP;
	}

	if (carl9170fw_supports(otus_desc->feature_set, CARL9170FW_USB_DOWN_STREAM)) {
		dbg("Enabled tx stream mode.\n");
		ar->tx_stream = true;
		ar->extra_headroom = sizeof(struct ar9170_stream);
	}

	if (carl9170fw_supports(otus_desc->feature_set, CARL9170FW_USB_UP_STREAM)) {
		dbg("Enabled rx stream mode.\n");
		ar->rx_stream = true;
	}

	if (carl9170fw_supports(otus_desc->feature_set, CARL9170FW_USB_RESP_EP2))
		dbg("Firmware sends traps over EP2.\n");

	ar->dma_chunk_size = le16_to_cpu(otus_desc->tx_frag_len);
	ar->dma_chunks = otus_desc->tx_descs;
	ar->rx_max = le16_to_cpu(otus_desc->rx_max_frame_len);

	if (carl9170fw_supports(otus_desc->feature_set, CARL9170FW_MINIBOOT))
		ar->miniboot_size = le16_to_cpu(otus_desc->miniboot_size);

	return 0;
}