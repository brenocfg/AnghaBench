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
typedef  int /*<<< orphan*/  u16 ;
struct nes_cm_node {int mpa_frame_rev; int /*<<< orphan*/  mpa_frame_size; int /*<<< orphan*/ * mpa_frame_buf; } ;
struct ietf_rtr_msg {int dummy; } ;
struct ietf_mpa_v2 {int dummy; } ;
struct ietf_mpa_v1 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IETF_MPA_V1 129 
#define  IETF_MPA_V2 128 
 int /*<<< orphan*/  build_mpa_v1 (struct nes_cm_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_mpa_v2 (struct nes_cm_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cm_build_mpa_frame(struct nes_cm_node *cm_node, u8 **start_buff,
			      u16 *buff_len, u8 *pci_mem, u8 mpa_key)
{
	int ret = 0;

	*start_buff = (pci_mem) ? pci_mem : &cm_node->mpa_frame_buf[0];

	switch (cm_node->mpa_frame_rev) {
	case IETF_MPA_V1:
		*start_buff = (u8 *)*start_buff + sizeof(struct ietf_rtr_msg);
		*buff_len = sizeof(struct ietf_mpa_v1) + cm_node->mpa_frame_size;
		build_mpa_v1(cm_node, *start_buff, mpa_key);
		break;
	case IETF_MPA_V2:
		*buff_len = sizeof(struct ietf_mpa_v2) + cm_node->mpa_frame_size;
		build_mpa_v2(cm_node, *start_buff, mpa_key);
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}