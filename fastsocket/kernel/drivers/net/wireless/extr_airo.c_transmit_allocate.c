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
typedef  int u16 ;
typedef  int /*<<< orphan*/  txControl ;
struct airo_info {int /*<<< orphan*/  sem; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {int parm0; int /*<<< orphan*/  cmd; } ;
struct TYPE_5__ {int status; } ;
typedef  TYPE_1__ Resp ;
typedef  TYPE_2__ Cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BAP1 ; 
 int /*<<< orphan*/  CMD_ALLOCATETX ; 
 int ERROR ; 
 int /*<<< orphan*/  EVACK ; 
 int /*<<< orphan*/  EVSTAT ; 
 int EV_ALLOC ; 
 int IN4500 (struct airo_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  TXALLOCFID ; 
 int TXCTL_802_11 ; 
 int TXCTL_802_3 ; 
 int TXCTL_ETHERNET ; 
 int TXCTL_NORELEASE ; 
 int TXCTL_TXEX ; 
 int TXCTL_TXOK ; 
 scalar_t__ bap_setup (struct airo_info*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bap_write (struct airo_info*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 scalar_t__ issuecommand (struct airo_info*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 transmit_allocate(struct airo_info *ai, int lenPayload, int raw)
{
	unsigned int loop = 3000;
	Cmd cmd;
	Resp rsp;
	u16 txFid;
	__le16 txControl;

	cmd.cmd = CMD_ALLOCATETX;
	cmd.parm0 = lenPayload;
	if (down_interruptible(&ai->sem))
		return ERROR;
	if (issuecommand(ai, &cmd, &rsp) != SUCCESS) {
		txFid = ERROR;
		goto done;
	}
	if ( (rsp.status & 0xFF00) != 0) {
		txFid = ERROR;
		goto done;
	}
	/* wait for the allocate event/indication
	 * It makes me kind of nervous that this can just sit here and spin,
	 * but in practice it only loops like four times. */
	while (((IN4500(ai, EVSTAT) & EV_ALLOC) == 0) && --loop);
	if (!loop) {
		txFid = ERROR;
		goto done;
	}

	// get the allocated fid and acknowledge
	txFid = IN4500(ai, TXALLOCFID);
	OUT4500(ai, EVACK, EV_ALLOC);

	/*  The CARD is pretty cool since it converts the ethernet packet
	 *  into 802.11.  Also note that we don't release the FID since we
	 *  will be using the same one over and over again. */
	/*  We only have to setup the control once since we are not
	 *  releasing the fid. */
	if (raw)
		txControl = cpu_to_le16(TXCTL_TXOK | TXCTL_TXEX | TXCTL_802_11
			| TXCTL_ETHERNET | TXCTL_NORELEASE);
	else
		txControl = cpu_to_le16(TXCTL_TXOK | TXCTL_TXEX | TXCTL_802_3
			| TXCTL_ETHERNET | TXCTL_NORELEASE);
	if (bap_setup(ai, txFid, 0x0008, BAP1) != SUCCESS)
		txFid = ERROR;
	else
		bap_write(ai, &txControl, sizeof(txControl), BAP1);

done:
	up(&ai->sem);

	return txFid;
}