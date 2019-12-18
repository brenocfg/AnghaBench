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
typedef  int /*<<< orphan*/  xTimerHandle ;
typedef  int uint8_t ;
struct os_mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  hrm ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int ble_gattc_notify_custom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct os_mbuf*) ; 
 struct os_mbuf* ble_hs_mbuf_from_flat (int*,int) ; 
 int /*<<< orphan*/  blehr_tx_hrate_reset () ; 
 int /*<<< orphan*/  blehr_tx_hrate_stop () ; 
 int /*<<< orphan*/  conn_handle ; 
 int heartrate ; 
 int /*<<< orphan*/  hrs_hrm_handle ; 
 int /*<<< orphan*/  notify_state ; 

__attribute__((used)) static void
blehr_tx_hrate(xTimerHandle ev)
{
    static uint8_t hrm[2];
    int rc;
    struct os_mbuf *om;

    if (!notify_state) {
        blehr_tx_hrate_stop();
        heartrate = 90;
        return;
    }

    hrm[0] = 0x06; /* contact of a sensor */
    hrm[1] = heartrate; /* storing dummy data */

    /* Simulation of heart beats */
    heartrate++;
    if (heartrate == 160) {
        heartrate = 90;
    }

    om = ble_hs_mbuf_from_flat(hrm, sizeof(hrm));
    rc = ble_gattc_notify_custom(conn_handle, hrs_hrm_handle, om);

    assert(rc == 0);

    blehr_tx_hrate_reset();
}