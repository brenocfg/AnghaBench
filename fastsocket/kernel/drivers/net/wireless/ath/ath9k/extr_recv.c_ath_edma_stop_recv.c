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

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_RX_QUEUE_HP ; 
 int /*<<< orphan*/  ATH9K_RX_QUEUE_LP ; 
 int /*<<< orphan*/  ath_rx_remove_buffer (struct ath_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath_edma_stop_recv(struct ath_softc *sc)
{
	ath_rx_remove_buffer(sc, ATH9K_RX_QUEUE_HP);
	ath_rx_remove_buffer(sc, ATH9K_RX_QUEUE_LP);
}