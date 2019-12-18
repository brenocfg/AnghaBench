#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uchar ;
struct TYPE_6__ {int max_sdtr_index; int /*<<< orphan*/  iop_base; } ;
struct TYPE_5__ {int xfer_period; int req_ack_offset; int /*<<< orphan*/  msg_req; int /*<<< orphan*/  msg_len; int /*<<< orphan*/  msg_type; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_1__ EXT_MSG ;
typedef  TYPE_2__ ASC_DVC_VAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASCV_MSGOUT_BEG ; 
 int ASC_SYN_MAX_OFFSET ; 
 int AscGetSynPeriodIndex (TYPE_2__*,int) ; 
 int /*<<< orphan*/  AscMemWordCopyPtrToLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  EXTENDED_MESSAGE ; 
 int /*<<< orphan*/  EXTENDED_SDTR ; 
 int /*<<< orphan*/  MS_SDTR_LEN ; 

__attribute__((used)) static uchar
AscMsgOutSDTR(ASC_DVC_VAR *asc_dvc, uchar sdtr_period, uchar sdtr_offset)
{
	EXT_MSG sdtr_buf;
	uchar sdtr_period_index;
	PortAddr iop_base;

	iop_base = asc_dvc->iop_base;
	sdtr_buf.msg_type = EXTENDED_MESSAGE;
	sdtr_buf.msg_len = MS_SDTR_LEN;
	sdtr_buf.msg_req = EXTENDED_SDTR;
	sdtr_buf.xfer_period = sdtr_period;
	sdtr_offset &= ASC_SYN_MAX_OFFSET;
	sdtr_buf.req_ack_offset = sdtr_offset;
	sdtr_period_index = AscGetSynPeriodIndex(asc_dvc, sdtr_period);
	if (sdtr_period_index <= asc_dvc->max_sdtr_index) {
		AscMemWordCopyPtrToLram(iop_base, ASCV_MSGOUT_BEG,
					(uchar *)&sdtr_buf,
					sizeof(EXT_MSG) >> 1);
		return ((sdtr_period_index << 4) | sdtr_offset);
	} else {
		sdtr_buf.req_ack_offset = 0;
		AscMemWordCopyPtrToLram(iop_base, ASCV_MSGOUT_BEG,
					(uchar *)&sdtr_buf,
					sizeof(EXT_MSG) >> 1);
		return 0;
	}
}