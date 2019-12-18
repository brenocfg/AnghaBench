#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {int nbchannel; } ;
struct capi_ctr {TYPE_1__ profile; scalar_t__ driverdata; } ;
struct TYPE_7__ {int level3cnt; int datablkcnt; int datablklen; } ;
typedef  TYPE_2__ capi_register_params ;
struct TYPE_8__ {TYPE_4__* card; } ;
typedef  TYPE_3__ avmctrl_info ;
struct TYPE_9__ {unsigned int port; int /*<<< orphan*/  lock; } ;
typedef  TYPE_4__ avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_REGISTER ; 
 int /*<<< orphan*/  b1_put_byte (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b1_put_word (unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void b1_register_appl(struct capi_ctr *ctrl,
				u16 appl,
				capi_register_params *rp)
{
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);
	avmcard *card = cinfo->card;
	unsigned int port = card->port;
	unsigned long flags;
	int nconn, want = rp->level3cnt;

	if (want > 0) nconn = want;
	else nconn = ctrl->profile.nbchannel * -want;
	if (nconn == 0) nconn = ctrl->profile.nbchannel;

	spin_lock_irqsave(&card->lock, flags);
	b1_put_byte(port, SEND_REGISTER);
	b1_put_word(port, appl);
	b1_put_word(port, 1024 * (nconn+1));
	b1_put_word(port, nconn);
	b1_put_word(port, rp->datablkcnt);
	b1_put_word(port, rp->datablklen);
	spin_unlock_irqrestore(&card->lock, flags);
}