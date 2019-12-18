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
struct il_spectrum_notification {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct il_spectrum_notification spectrum_notif; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct il_priv {int /*<<< orphan*/  measurement_status; int /*<<< orphan*/  measure_report; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_11H (char*) ; 
 int /*<<< orphan*/  MEASUREMENT_READY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct il_spectrum_notification*,int) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

void
il_hdl_spectrum_measurement(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_spectrum_notification *report = &(pkt->u.spectrum_notif);

	if (!report->state) {
		D_11H("Spectrum Measure Notification: Start\n");
		return;
	}

	memcpy(&il->measure_report, report, sizeof(*report));
	il->measurement_status |= MEASUREMENT_READY;
}