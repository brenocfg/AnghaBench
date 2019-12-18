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
struct scsi_cmnd {scalar_t__ host_scribble; } ;
struct dc390_srb {int SRBState; int MsgCnt; int /*<<< orphan*/ * MsgOutBuf; TYPE_1__* pcmd; } ;
struct dc390_dcb {int DCBFlag; struct dc390_srb* pActiveSRB; struct dc390_srb* pGoingSRB; } ;
struct dc390_acb {struct dc390_srb* pTmpSRB; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ABORT_DEV_ ; 
 int /*<<< orphan*/  ABORT_TAG ; 
 int /*<<< orphan*/  DC390_ENABLE_MSGOUT ; 
 int SRB_ABORT_SENT ; 
 int SRB_DATA_XFER ; 
 int SRB_DISCONNECT ; 
 int SRB_UNEXPECT_RESEL ; 
 int /*<<< orphan*/  dc390_EnableMsgOut_Abort (struct dc390_acb*,struct dc390_srb*) ; 
 struct scsi_cmnd* scsi_find_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dc390_srb*
dc390_MsgIn_QTag (struct dc390_acb* pACB, struct dc390_dcb* pDCB, s8 tag)
{
  struct dc390_srb* pSRB = pDCB->pGoingSRB;

  if (pSRB)
    {
	struct scsi_cmnd *scmd = scsi_find_tag(pSRB->pcmd->device, tag);
	pSRB = (struct dc390_srb *)scmd->host_scribble;

	if (pDCB->DCBFlag & ABORT_DEV_)
	{
	  pSRB->SRBState = SRB_ABORT_SENT;
	  dc390_EnableMsgOut_Abort( pACB, pSRB );
	}

	if (!(pSRB->SRBState & SRB_DISCONNECT))
		goto mingx0;

	pDCB->pActiveSRB = pSRB;
	pSRB->SRBState = SRB_DATA_XFER;
    }
  else
    {
    mingx0:
      pSRB = pACB->pTmpSRB;
      pSRB->SRBState = SRB_UNEXPECT_RESEL;
      pDCB->pActiveSRB = pSRB;
      pSRB->MsgOutBuf[0] = ABORT_TAG;
      pSRB->MsgCnt = 1; DC390_ENABLE_MSGOUT;
    }
  return pSRB;
}