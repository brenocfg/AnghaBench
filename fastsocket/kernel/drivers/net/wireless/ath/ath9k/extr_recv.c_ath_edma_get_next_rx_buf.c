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
struct ath_softc {int dummy; } ;
struct ath_rx_status {int dummy; } ;
struct ath_buf {int dummy; } ;
typedef  enum ath9k_rx_qtype { ____Placeholder_ath9k_rx_qtype } ath9k_rx_qtype ;

/* Variables and functions */
 scalar_t__ ath_edma_get_buffers (struct ath_softc*,int,struct ath_rx_status*,struct ath_buf**) ; 

__attribute__((used)) static struct ath_buf *ath_edma_get_next_rx_buf(struct ath_softc *sc,
						struct ath_rx_status *rs,
						enum ath9k_rx_qtype qtype)
{
	struct ath_buf *bf = NULL;

	while (ath_edma_get_buffers(sc, qtype, rs, &bf)) {
		if (!bf)
			continue;

		return bf;
	}
	return NULL;
}