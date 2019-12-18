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
typedef  scalar_t__ uint16_t ;
struct peer {scalar_t__ conn_handle; int /*<<< orphan*/  disc_prev_chr_val; } ;
struct ble_gatt_error {int status; } ;
struct ble_gatt_dsc {int dummy; } ;

/* Variables and functions */
#define  BLE_HS_EDONE 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  peer_disc_complete (struct peer*,int) ; 
 int /*<<< orphan*/  peer_disc_dscs (struct peer*) ; 
 int peer_dsc_add (struct peer*,scalar_t__,struct ble_gatt_dsc const*) ; 

__attribute__((used)) static int
peer_dsc_disced(uint16_t conn_handle, const struct ble_gatt_error *error,
                uint16_t chr_val_handle, const struct ble_gatt_dsc *dsc,
                void *arg)
{
    struct peer *peer;
    int rc;

    peer = arg;
    assert(peer->conn_handle == conn_handle);

    switch (error->status) {
    case 0:
        rc = peer_dsc_add(peer, chr_val_handle, dsc);
        break;

    case BLE_HS_EDONE:
        /* All descriptors in this characteristic discovered; start discovering
         * descriptors in the next characteristic.
         */
        if (peer->disc_prev_chr_val > 0) {
            peer_disc_dscs(peer);
        }
        rc = 0;
        break;

    default:
        /* Error; abort discovery. */
        rc = error->status;
        break;
    }

    if (rc != 0) {
        /* Error; abort discovery. */
        peer_disc_complete(peer, rc);
    }

    return rc;
}