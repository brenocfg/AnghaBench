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
struct msm_adsp_module {int dummy; } ;
struct TYPE_3__ {scalar_t__ msg16; } ;
struct adsp_event {scalar_t__ msg_id; TYPE_1__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  op_buf_addr; } ;
typedef  TYPE_2__ jpeg_msg_enc_op_produced ;

/* Variables and functions */
 scalar_t__ JPEG_MSG_ENC_OP_PRODUCED ; 
 int adsp_pmem_paddr_fixup (struct msm_adsp_module*,void**) ; 

int adsp_jpeg_patch_event(struct msm_adsp_module *module,
			struct adsp_event *event)
{
	if (event->msg_id == JPEG_MSG_ENC_OP_PRODUCED) {
		jpeg_msg_enc_op_produced *op = (jpeg_msg_enc_op_produced *)event->data.msg16;
		return adsp_pmem_paddr_fixup(module, (void **)&op->op_buf_addr);
	}

	return 0;
}