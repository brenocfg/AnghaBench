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
struct TYPE_3__ {TYPE_2__* txq; } ;
struct ath_softc {TYPE_1__ tx; } ;
struct TYPE_4__ {int /*<<< orphan*/  axq_lock; } ;

/* Variables and functions */
 int ATH9K_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  ATH_TXQ_SETUP (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int ath_reset_internal (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_txq_schedule (struct ath_softc*,TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath_reset(struct ath_softc *sc)
{
	int i, r;

	ath9k_ps_wakeup(sc);

	r = ath_reset_internal(sc, NULL);

	for (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) {
		if (!ATH_TXQ_SETUP(sc, i))
			continue;

		spin_lock_bh(&sc->tx.txq[i].axq_lock);
		ath_txq_schedule(sc, &sc->tx.txq[i]);
		spin_unlock_bh(&sc->tx.txq[i].axq_lock);
	}

	ath9k_ps_restore(sc);

	return r;
}