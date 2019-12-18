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
struct carlfw {int dummy; } ;
struct carl9170fw_otus_desc {int fw_address; int tx_frag_len; int tx_descs; int cmd_bufs; int rx_max_frame_len; int vif_num; int api_ver; int /*<<< orphan*/  feature_set; int /*<<< orphan*/  bcn_len; int /*<<< orphan*/  bcn_addr; } ;
struct carl9170fw_desc_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ __CARL9170FW_FEATURE_NUM ; 
 int /*<<< orphan*/  check_feature_list (struct carl9170fw_desc_head const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct carlfw*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  known_otus_features_v1 ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void show_otus_desc(const struct carl9170fw_desc_head *head,
			   struct carlfw *fw)
{
	const struct carl9170fw_otus_desc *otus = (const void *) head;

	BUILD_BUG_ON(ARRAY_SIZE(known_otus_features_v1) != __CARL9170FW_FEATURE_NUM);

	fprintf(stdout, "\tFirmware upload pointer: 0x%x\n",
		otus->fw_address);
	fprintf(stdout, "\tBeacon Address: %x, (reserved:%d Bytes)\n",
		le32_to_cpu(otus->bcn_addr), le16_to_cpu(otus->bcn_len));
	fprintf(stdout, "\tTX DMA chunk size:%d Bytes, TX DMA chunks:%d\n",
		otus->tx_frag_len, otus->tx_descs);
	fprintf(stdout, "\t=> %d Bytes are reserved for the TX queues\n",
		otus->tx_frag_len * otus->tx_descs);
	fprintf(stdout, "\tCommand response buffers:%d\n", otus->cmd_bufs);
	fprintf(stdout, "\tMax. RX stream block size:%d Bytes\n",
		otus->rx_max_frame_len);
	fprintf(stdout, "\tSupported Firmware Interfaces: %d\n", otus->vif_num);
	fprintf(stdout, "\tFirmware API Version: %d\n", otus->api_ver);
	fprintf(stdout, "\tSupported Features: (raw:%.08x)\n",
		le32_to_cpu(otus->feature_set));

	check_feature_list(head, otus->feature_set, known_otus_features_v1,
			   ARRAY_SIZE(known_otus_features_v1), fw);
}