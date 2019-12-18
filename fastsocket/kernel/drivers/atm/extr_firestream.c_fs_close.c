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
struct fs_vcc {int channo; int /*<<< orphan*/  close_wait; struct fs_vcc* last_skb; } ;
struct fs_dev {int /*<<< orphan*/  hp_txq; int /*<<< orphan*/ ** atm_vccs; int /*<<< orphan*/ * tx_inuse; struct fs_vcc* ntxpckts; } ;
struct atm_trafprm {int dummy; } ;
struct TYPE_2__ {struct atm_trafprm rxtp; struct atm_trafprm txtp; } ;
struct atm_vcc {TYPE_1__ qos; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATM_VF_READY ; 
 scalar_t__ DO_DIRECTION (struct atm_trafprm*) ; 
 int /*<<< orphan*/  FS_DEBUG_ALLOC ; 
 int /*<<< orphan*/  FS_DEBUG_QSIZE ; 
 int /*<<< orphan*/  FS_DEBUG_QUEUE ; 
 struct fs_dev* FS_DEV (int /*<<< orphan*/ ) ; 
 struct fs_vcc* FS_VCC (struct atm_vcc*) ; 
 scalar_t__ IS_FS50 (struct fs_dev*) ; 
 int QE_CMD_IMM_INQ ; 
 int QE_CMD_REG_WR ; 
 int QE_CMD_RX_PURGE_INH ; 
 int QE_CMD_TX_PURGE_INH ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_dprintk (int /*<<< orphan*/ ,char*,struct fs_vcc*) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fs_vcc*) ; 
 int /*<<< orphan*/  submit_command (struct fs_dev*,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs_close(struct atm_vcc *atm_vcc)
{
	struct fs_dev *dev = FS_DEV (atm_vcc->dev);
	struct fs_vcc *vcc = FS_VCC (atm_vcc);
	struct atm_trafprm * txtp;
	struct atm_trafprm * rxtp;

	func_enter ();

	clear_bit(ATM_VF_READY, &atm_vcc->flags);

	fs_dprintk (FS_DEBUG_QSIZE, "--==**[%d]**==--", dev->ntxpckts);
	if (vcc->last_skb) {
		fs_dprintk (FS_DEBUG_QUEUE, "Waiting for skb %p to be sent.\n", 
			    vcc->last_skb);
		/* We're going to wait for the last packet to get sent on this VC. It would
		   be impolite not to send them don't you think? 
		   XXX
		   We don't know which packets didn't get sent. So if we get interrupted in 
		   this sleep_on, we'll lose any reference to these packets. Memory leak!
		   On the other hand, it's awfully convenient that we can abort a "close" that
		   is taking too long. Maybe just use non-interruptible sleep on? -- REW */
		interruptible_sleep_on (& vcc->close_wait);
	}

	txtp = &atm_vcc->qos.txtp;
	rxtp = &atm_vcc->qos.rxtp;
  

	/* See App note XXX (Unpublished as of now) for the reason for the 
	   removal of the "CMD_IMM_INQ" part of the TX_PURGE_INH... -- REW */

	if (DO_DIRECTION (txtp)) {
		submit_command (dev,  &dev->hp_txq,
				QE_CMD_TX_PURGE_INH | /*QE_CMD_IMM_INQ|*/ vcc->channo, 0,0,0);
		clear_bit (vcc->channo, dev->tx_inuse);
	}

	if (DO_DIRECTION (rxtp)) {
		submit_command (dev,  &dev->hp_txq,
				QE_CMD_RX_PURGE_INH | QE_CMD_IMM_INQ | vcc->channo, 0,0,0);
		dev->atm_vccs [vcc->channo] = NULL;
  
		/* This means that this is configured as a receive channel */
		if (IS_FS50 (dev)) {
			/* Disable the receive filter. Is 0/0 indeed an invalid receive
			   channel? -- REW.  Yes it is. -- Hang. Ok. I'll use -1
			   (0xfff...) -- REW */
			submit_command (dev, &dev->hp_txq, 
					QE_CMD_REG_WR | QE_CMD_IMM_INQ,
					0x80 + vcc->channo, -1, 0 ); 
		}
	}

	fs_dprintk (FS_DEBUG_ALLOC, "Free vcc: %p\n", vcc);
	kfree (vcc);

	func_exit ();
}