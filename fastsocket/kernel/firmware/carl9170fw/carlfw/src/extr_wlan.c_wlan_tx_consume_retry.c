#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int cnt; size_t rix; TYPE_6__* ri; TYPE_2__* rr; } ;
struct TYPE_10__ {int /*<<< orphan*/  ampdu; int /*<<< orphan*/  erp_prot; } ;
struct TYPE_8__ {scalar_t__ set; } ;
struct TYPE_11__ {TYPE_3__ mac; TYPE_1__ phy; } ;
struct TYPE_12__ {TYPE_4__ hdr; } ;
struct carl9170_tx_superframe {TYPE_7__ s; TYPE_5__ f; } ;
struct TYPE_13__ {int tries; int /*<<< orphan*/  ampdu; int /*<<< orphan*/  erp_prot; } ;
struct TYPE_9__ {scalar_t__ set; } ;

/* Variables and functions */
 size_t CARL9170_TX_MAX_RETRY_RATES ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool wlan_tx_consume_retry(struct carl9170_tx_superframe *super)
{
	/* check if this was the last possible retry with this rate */
	if (unlikely(super->s.cnt >= super->s.ri[super->s.rix].tries)) {
		/* end of the road - indicate tx failure */
		if (unlikely(super->s.rix == CARL9170_TX_MAX_RETRY_RATES))
			return false;

		/* check if there are alternative rates available */
		if (!super->s.rr[super->s.rix].set)
			return false;

		/* try next retry rate */
		super->f.hdr.phy.set = super->s.rr[super->s.rix].set;

		/* finally - mark the old rate as USED */
		super->s.rix++;

		/* update MAC flags */
		super->f.hdr.mac.erp_prot = super->s.ri[super->s.rix].erp_prot;
		super->f.hdr.mac.ampdu = super->s.ri[super->s.rix].ampdu;

		/* reinitialize try counter */
		super->s.cnt = 1;
	} else {
		/* just increase retry counter */
		super->s.cnt++;
	}

	return true;
}