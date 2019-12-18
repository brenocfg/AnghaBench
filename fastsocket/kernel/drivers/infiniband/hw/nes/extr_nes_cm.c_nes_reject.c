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
typedef  void* u8 ;
struct TYPE_3__ {void* priv_data; void* priv_data_len; } ;
struct nes_cm_node {void** mpa_frame_buf; void* mpa_frame_size; TYPE_1__ mpa_frame; struct iw_cm_id* cm_id; struct nes_cm_core* cm_core; struct nes_cm_node* loopbackpartner; } ;
struct nes_cm_core {TYPE_2__* api; } ;
struct iw_cm_id {scalar_t__ provider_data; } ;
struct ietf_mpa_v2 {int dummy; } ;
struct TYPE_4__ {int (* reject ) (struct nes_cm_core*,struct nes_cm_node*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_CM_BUFFER ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_rejects ; 
 int /*<<< orphan*/  memcpy (void**,void const*,void*) ; 
 int stub1 (struct nes_cm_core*,struct nes_cm_node*) ; 

int nes_reject(struct iw_cm_id *cm_id, const void *pdata, u8 pdata_len)
{
	struct nes_cm_node *cm_node;
	struct nes_cm_node *loopback;
	struct nes_cm_core *cm_core;
	u8 *start_buff;

	atomic_inc(&cm_rejects);
	cm_node = (struct nes_cm_node *)cm_id->provider_data;
	loopback = cm_node->loopbackpartner;
	cm_core = cm_node->cm_core;
	cm_node->cm_id = cm_id;

	if (pdata_len + sizeof(struct ietf_mpa_v2) > MAX_CM_BUFFER)
		return -EINVAL;

	if (loopback) {
		memcpy(&loopback->mpa_frame.priv_data, pdata, pdata_len);
		loopback->mpa_frame.priv_data_len = pdata_len;
		loopback->mpa_frame_size = pdata_len;
	} else {
		start_buff = &cm_node->mpa_frame_buf[0] + sizeof(struct ietf_mpa_v2);
		cm_node->mpa_frame_size = pdata_len;
		memcpy(start_buff, pdata, pdata_len);
	}
	return cm_core->api->reject(cm_core, cm_node);
}