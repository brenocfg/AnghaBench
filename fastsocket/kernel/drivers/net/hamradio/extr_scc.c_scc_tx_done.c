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
struct TYPE_3__ {int fulldup; int idletime; int tailtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_state; } ;
struct scc_channel {int /*<<< orphan*/  dev; TYPE_1__ kiss; TYPE_2__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWEV_ALL_SENT ; 
#define  KISS_DUPLEX_LINK 129 
#define  KISS_DUPLEX_OPTIMA 128 
 int TIMER_OFF ; 
 int /*<<< orphan*/  TXS_BUSY ; 
 int /*<<< orphan*/  TXS_IDLE2 ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_notify (struct scc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_start_tx_timer (struct scc_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t_idle ; 
 int /*<<< orphan*/  t_tail ; 

__attribute__((used)) static void scc_tx_done(struct scc_channel *scc)
{
	/* 
	 * trx remains keyed in fulldup mode 2 until t_idle expires.
	 */
				 
	switch (scc->kiss.fulldup)
	{
		case KISS_DUPLEX_LINK:
			scc->stat.tx_state = TXS_IDLE2;
			if (scc->kiss.idletime != TIMER_OFF)
			scc_start_tx_timer(scc, t_idle, scc->kiss.idletime*100);
			break;
		case KISS_DUPLEX_OPTIMA:
			scc_notify(scc, HWEV_ALL_SENT);
			break;
		default:
			scc->stat.tx_state = TXS_BUSY;
			scc_start_tx_timer(scc, t_tail, scc->kiss.tailtime);
	}

	netif_wake_queue(scc->dev);
}