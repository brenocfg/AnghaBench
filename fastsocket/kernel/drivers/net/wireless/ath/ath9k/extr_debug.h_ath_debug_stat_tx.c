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
struct ath_txq {int dummy; } ;
struct ath_tx_status {int dummy; } ;
struct ath_softc {int dummy; } ;
struct ath_buf {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void ath_debug_stat_tx(struct ath_softc *sc,
				     struct ath_buf *bf,
				     struct ath_tx_status *ts,
				     struct ath_txq *txq,
				     unsigned int flags)
{
}