#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct pau_fpdu_info {int hdr_len; TYPE_1__* frags; scalar_t__ hdr_pbase; scalar_t__ data_len; struct nes_cqp_request* cqp_request; } ;
struct nes_vnic {scalar_t__ logical_port; struct nes_device* nesdev; } ;
struct nes_qp {int dummy; } ;
struct nes_hw_cqp_wqe {int /*<<< orphan*/  wqe_words; } ;
struct nes_device {int dummy; } ;
struct nes_cqp_request {int callback; int /*<<< orphan*/  refcount; int /*<<< orphan*/  cqp_callback; struct pau_fpdu_info* cqp_callback_pointer; struct nes_hw_cqp_wqe cqp_wqe; } ;
struct TYPE_2__ {int frag_len; int physaddr; } ;

/* Variables and functions */
 int NES_CQP_DOWNLOAD_SEGMENT ; 
 int NES_CQP_OP_LOGICAL_PORT_SHIFT ; 
 int /*<<< orphan*/  NES_CQP_WQE_DL_LENGTH_0_TOTAL_IDX ; 
 int /*<<< orphan*/  NES_CQP_WQE_DL_OPCODE_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_FRAG0_HIGH_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_FRAG0_LOW_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_FRAG1_HIGH_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_FRAG1_LOW_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_FRAG2_HIGH_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_FRAG2_LOW_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_FRAG3_HIGH_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_FRAG3_LOW_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_FRAG4_HIGH_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_FRAG4_LOW_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_LENGTH_2_1_IDX ; 
 int /*<<< orphan*/  NES_NIC_SQ_WQE_LENGTH_4_3_IDX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int get_fpdu_info (struct nes_device*,struct nes_qp*,struct pau_fpdu_info**) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  nes_download_callback ; 
 int /*<<< orphan*/  nes_fill_init_cqp_wqe (struct nes_hw_cqp_wqe*,struct nes_device*) ; 
 int /*<<< orphan*/  nes_post_cqp_request (struct nes_device*,struct nes_cqp_request*) ; 
 int /*<<< orphan*/  set_wqe_32bit_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int forward_fpdus(struct nes_vnic *nesvnic, struct nes_qp *nesqp)
{
	struct nes_device *nesdev = nesvnic->nesdev;
	struct pau_fpdu_info *fpdu_info;
	struct nes_hw_cqp_wqe *cqp_wqe;
	struct nes_cqp_request *cqp_request;
	u64 u64tmp;
	u32 u32tmp;
	int rc;

	while (1) {
		rc = get_fpdu_info(nesdev, nesqp, &fpdu_info);
		if (fpdu_info == NULL)
			return rc;

		cqp_request = fpdu_info->cqp_request;
		cqp_wqe = &cqp_request->cqp_wqe;
		nes_fill_init_cqp_wqe(cqp_wqe, nesdev);
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_WQE_DL_OPCODE_IDX,
				    NES_CQP_DOWNLOAD_SEGMENT |
				    (((u32)nesvnic->logical_port) << NES_CQP_OP_LOGICAL_PORT_SHIFT));

		u32tmp = fpdu_info->hdr_len << 16;
		u32tmp |= fpdu_info->hdr_len + (u32)fpdu_info->data_len;
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_WQE_DL_LENGTH_0_TOTAL_IDX,
				    u32tmp);

		u32tmp = (fpdu_info->frags[1].frag_len << 16) | fpdu_info->frags[0].frag_len;
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_LENGTH_2_1_IDX,
				    u32tmp);

		u32tmp = (fpdu_info->frags[3].frag_len << 16) | fpdu_info->frags[2].frag_len;
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_LENGTH_4_3_IDX,
				    u32tmp);

		u64tmp = (u64)fpdu_info->hdr_pbase;
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_FRAG0_LOW_IDX,
				    lower_32_bits(u64tmp));
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_FRAG0_HIGH_IDX,
				    upper_32_bits(u64tmp >> 32));

		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_FRAG1_LOW_IDX,
				    lower_32_bits(fpdu_info->frags[0].physaddr));
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_FRAG1_HIGH_IDX,
				    upper_32_bits(fpdu_info->frags[0].physaddr));

		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_FRAG2_LOW_IDX,
				    lower_32_bits(fpdu_info->frags[1].physaddr));
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_FRAG2_HIGH_IDX,
				    upper_32_bits(fpdu_info->frags[1].physaddr));

		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_FRAG3_LOW_IDX,
				    lower_32_bits(fpdu_info->frags[2].physaddr));
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_FRAG3_HIGH_IDX,
				    upper_32_bits(fpdu_info->frags[2].physaddr));

		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_FRAG4_LOW_IDX,
				    lower_32_bits(fpdu_info->frags[3].physaddr));
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_NIC_SQ_WQE_FRAG4_HIGH_IDX,
				    upper_32_bits(fpdu_info->frags[3].physaddr));

		cqp_request->cqp_callback_pointer = fpdu_info;
		cqp_request->callback = 1;
		cqp_request->cqp_callback = nes_download_callback;

		atomic_set(&cqp_request->refcount, 1);
		nes_post_cqp_request(nesdev, cqp_request);
	}

	return 0;
}