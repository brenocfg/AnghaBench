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
typedef  int u16 ;
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCONEXIST ; 
 int /*<<< orphan*/  CSEQ_BUILTIN_FREE_SCB_HEAD ; 
 int /*<<< orphan*/  CSEQ_BUILTIN_FREE_SCB_TAIL ; 
 scalar_t__ CSEQ_EMPTY_REQ_COUNT ; 
 int /*<<< orphan*/  CSEQ_EMPTY_REQ_HEAD ; 
 scalar_t__ CSEQ_EMPTY_REQ_QUEUE ; 
 int /*<<< orphan*/  CSEQ_EMPTY_REQ_TAIL ; 
 int /*<<< orphan*/  CSEQ_EMPTY_SCB_OFFSET ; 
 scalar_t__ CSEQ_EST_NEXUS_REQ_COUNT ; 
 int /*<<< orphan*/  CSEQ_EST_NEXUS_REQ_HEAD ; 
 scalar_t__ CSEQ_EST_NEXUS_REQ_QUEUE ; 
 int /*<<< orphan*/  CSEQ_EST_NEXUS_REQ_TAIL ; 
 int /*<<< orphan*/  CSEQ_EST_NEXUS_SCB_OFFSET ; 
 int /*<<< orphan*/  CSEQ_EXTENDED_FREE_SCB_HEAD ; 
 int /*<<< orphan*/  CSEQ_EXTENDED_FREE_SCB_TAIL ; 
 int /*<<< orphan*/  CSEQ_FREE_LIST_HACK_COUNT ; 
 int /*<<< orphan*/  CSEQ_FREE_SCB_MASK ; 
 int /*<<< orphan*/  CSEQ_INT_ROUT_MODE ; 
 int /*<<< orphan*/  CSEQ_INT_ROUT_RET_ADDR0 ; 
 int /*<<< orphan*/  CSEQ_INT_ROUT_RET_ADDR1 ; 
 int /*<<< orphan*/  CSEQ_INT_ROUT_SCBPTR ; 
 int /*<<< orphan*/  CSEQ_ISR_SAVE_DINDEX ; 
 int /*<<< orphan*/  CSEQ_ISR_SAVE_SINDEX ; 
 int /*<<< orphan*/  CSEQ_ISR_SCRATCH_FLAGS ; 
 int /*<<< orphan*/  CSEQ_LINK_CTL_Q_MAP ; 
 int /*<<< orphan*/  CSEQ_MAX_CSEQ_MODE ; 
 int /*<<< orphan*/  CSEQ_NEED_EMPTY_SCB ; 
 int /*<<< orphan*/  CSEQ_NEED_EST_NEXUS_SCB ; 
 int /*<<< orphan*/  CSEQ_PRIMITIVE_DATA ; 
 int /*<<< orphan*/  CSEQ_Q_COPY_HEAD ; 
 int /*<<< orphan*/  CSEQ_Q_COPY_TAIL ; 
 int /*<<< orphan*/  CSEQ_Q_DMA2CHIM_HEAD ; 
 int /*<<< orphan*/  CSEQ_Q_DMA2CHIM_TAIL ; 
 int /*<<< orphan*/  CSEQ_Q_DONE_HEAD ; 
 int /*<<< orphan*/  CSEQ_Q_DONE_TAIL ; 
 int /*<<< orphan*/  CSEQ_Q_EMPTY_HEAD ; 
 int /*<<< orphan*/  CSEQ_Q_EMPTY_TAIL ; 
 int /*<<< orphan*/  CSEQ_Q_EST_NEXUS_HEAD ; 
 int /*<<< orphan*/  CSEQ_Q_EST_NEXUS_TAIL ; 
 int /*<<< orphan*/  CSEQ_Q_EXE_HEAD ; 
 int /*<<< orphan*/  CSEQ_Q_EXE_TAIL ; 
 int /*<<< orphan*/  CSEQ_Q_MONIRTT_HEAD ; 
 int /*<<< orphan*/  CSEQ_Q_MONIRTT_TAIL ; 
 int /*<<< orphan*/  CSEQ_Q_SEND_HEAD ; 
 int /*<<< orphan*/  CSEQ_Q_SEND_TAIL ; 
 int /*<<< orphan*/  CSEQ_REG0 ; 
 int /*<<< orphan*/  CSEQ_REG1 ; 
 scalar_t__ CSEQ_REG2 ; 
 scalar_t__ CSEQ_TIMEOUT_CONST ; 
 int asd_get_cmdctx_size (struct asd_ha_struct*) ; 
 int asd_read_reg_byte (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_byte (struct asd_ha_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_word (struct asd_ha_struct*,int /*<<< orphan*/ ,int) ; 
 int first_scb_site_no ; 
 int hweight8 (int) ; 
 int last_scb_site_no ; 

__attribute__((used)) static void asd_init_cseq_mip(struct asd_ha_struct *asd_ha)
{
	/* CSEQ Mode Independent, page 4 setup. */
	asd_write_reg_word(asd_ha, CSEQ_Q_EXE_HEAD, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_EXE_TAIL, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_DONE_HEAD, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_DONE_TAIL, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_SEND_HEAD, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_SEND_TAIL, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_DMA2CHIM_HEAD, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_DMA2CHIM_TAIL, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_COPY_HEAD, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_COPY_TAIL, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_REG0, 0);
	asd_write_reg_word(asd_ha, CSEQ_REG1, 0);
	asd_write_reg_dword(asd_ha, CSEQ_REG2, 0);
	asd_write_reg_byte(asd_ha, CSEQ_LINK_CTL_Q_MAP, 0);
	{
		u8 con = asd_read_reg_byte(asd_ha, CCONEXIST);
		u8 val = hweight8(con);
		asd_write_reg_byte(asd_ha, CSEQ_MAX_CSEQ_MODE, (val<<4)|val);
	}
	asd_write_reg_word(asd_ha, CSEQ_FREE_LIST_HACK_COUNT, 0);

	/* CSEQ Mode independent, page 5 setup. */
	asd_write_reg_dword(asd_ha, CSEQ_EST_NEXUS_REQ_QUEUE, 0);
	asd_write_reg_dword(asd_ha, CSEQ_EST_NEXUS_REQ_QUEUE+4, 0);
	asd_write_reg_dword(asd_ha, CSEQ_EST_NEXUS_REQ_COUNT, 0);
	asd_write_reg_dword(asd_ha, CSEQ_EST_NEXUS_REQ_COUNT+4, 0);
	asd_write_reg_word(asd_ha, CSEQ_Q_EST_NEXUS_HEAD, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_EST_NEXUS_TAIL, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_NEED_EST_NEXUS_SCB, 0);
	asd_write_reg_byte(asd_ha, CSEQ_EST_NEXUS_REQ_HEAD, 0);
	asd_write_reg_byte(asd_ha, CSEQ_EST_NEXUS_REQ_TAIL, 0);
	asd_write_reg_byte(asd_ha, CSEQ_EST_NEXUS_SCB_OFFSET, 0);

	/* CSEQ Mode independent, page 6 setup. */
	asd_write_reg_word(asd_ha, CSEQ_INT_ROUT_RET_ADDR0, 0);
	asd_write_reg_word(asd_ha, CSEQ_INT_ROUT_RET_ADDR1, 0);
	asd_write_reg_word(asd_ha, CSEQ_INT_ROUT_SCBPTR, 0);
	asd_write_reg_byte(asd_ha, CSEQ_INT_ROUT_MODE, 0);
	asd_write_reg_byte(asd_ha, CSEQ_ISR_SCRATCH_FLAGS, 0);
	asd_write_reg_word(asd_ha, CSEQ_ISR_SAVE_SINDEX, 0);
	asd_write_reg_word(asd_ha, CSEQ_ISR_SAVE_DINDEX, 0);
	asd_write_reg_word(asd_ha, CSEQ_Q_MONIRTT_HEAD, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_MONIRTT_TAIL, 0xFFFF);
	/* Calculate the free scb mask. */
	{
		u16 cmdctx = asd_get_cmdctx_size(asd_ha);
		cmdctx = (~((cmdctx/128)-1)) >> 8;
		asd_write_reg_byte(asd_ha, CSEQ_FREE_SCB_MASK, (u8)cmdctx);
	}
	asd_write_reg_word(asd_ha, CSEQ_BUILTIN_FREE_SCB_HEAD,
			   first_scb_site_no);
	asd_write_reg_word(asd_ha, CSEQ_BUILTIN_FREE_SCB_TAIL,
			   last_scb_site_no);
	asd_write_reg_word(asd_ha, CSEQ_EXTENDED_FREE_SCB_HEAD, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_EXTENDED_FREE_SCB_TAIL, 0xFFFF);

	/* CSEQ Mode independent, page 7 setup. */
	asd_write_reg_dword(asd_ha, CSEQ_EMPTY_REQ_QUEUE, 0);
	asd_write_reg_dword(asd_ha, CSEQ_EMPTY_REQ_QUEUE+4, 0);
	asd_write_reg_dword(asd_ha, CSEQ_EMPTY_REQ_COUNT, 0);
	asd_write_reg_dword(asd_ha, CSEQ_EMPTY_REQ_COUNT+4, 0);
	asd_write_reg_word(asd_ha, CSEQ_Q_EMPTY_HEAD, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_Q_EMPTY_TAIL, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_NEED_EMPTY_SCB, 0);
	asd_write_reg_byte(asd_ha, CSEQ_EMPTY_REQ_HEAD, 0);
	asd_write_reg_byte(asd_ha, CSEQ_EMPTY_REQ_TAIL, 0);
	asd_write_reg_byte(asd_ha, CSEQ_EMPTY_SCB_OFFSET, 0);
	asd_write_reg_word(asd_ha, CSEQ_PRIMITIVE_DATA, 0);
	asd_write_reg_dword(asd_ha, CSEQ_TIMEOUT_CONST, 0);
}