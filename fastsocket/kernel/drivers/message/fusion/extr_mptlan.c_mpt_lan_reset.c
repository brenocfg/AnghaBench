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
struct net_device {int dummy; } ;
struct mpt_lan_priv {int /*<<< orphan*/  mpt_dev; int /*<<< orphan*/  pnum; } ;
struct TYPE_2__ {scalar_t__ Reserved2; scalar_t__ MsgFlags; int /*<<< orphan*/  PortNumber; scalar_t__ Reserved; scalar_t__ ChainOffset; int /*<<< orphan*/  Function; } ;
typedef  int /*<<< orphan*/  MPT_FRAME_HDR ;
typedef  TYPE_1__ LANResetRequest_t ;

/* Variables and functions */
 int /*<<< orphan*/  LanCtx ; 
 int /*<<< orphan*/  MPI_FUNCTION_LAN_RESET ; 
 int /*<<< orphan*/ * mpt_get_msg_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_put_msg_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mpt_lan_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
mpt_lan_reset(struct net_device *dev)
{
	MPT_FRAME_HDR *mf;
	LANResetRequest_t *pResetReq;
	struct mpt_lan_priv *priv = netdev_priv(dev);

	mf = mpt_get_msg_frame(LanCtx, priv->mpt_dev);

	if (mf == NULL) {
/*		dlprintk((KERN_ERR MYNAM "/reset: Evil funkiness abounds! "
		"Unable to allocate a request frame.\n"));
*/
		return -1;
	}

	pResetReq = (LANResetRequest_t *) mf;

	pResetReq->Function	= MPI_FUNCTION_LAN_RESET;
	pResetReq->ChainOffset	= 0;
	pResetReq->Reserved	= 0;
	pResetReq->PortNumber	= priv->pnum;
	pResetReq->MsgFlags	= 0;
	pResetReq->Reserved2	= 0;

	mpt_put_msg_frame(LanCtx, priv->mpt_dev, mf);

	return 0;
}