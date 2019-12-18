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
struct ble_gatt_svc {int dummy; } ;
struct ble_gatt_error {int status; } ;

/* Variables and functions */
#define  BLE_HS_EDONE 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  peer_disc_chrs (struct peer*) ; 
 int /*<<< orphan*/  peer_disc_complete (struct peer*,int) ; 
 int peer_svc_add (struct peer*,struct ble_gatt_svc const*) ; 

__attribute__((used)) static int
peer_svc_disced(uint16_t conn_handle, const struct ble_gatt_error *error,
                const struct ble_gatt_svc *service, void *arg)
{
    struct peer *peer;
    int rc;

    peer = arg;
    assert(peer->conn_handle == conn_handle);

    switch (error->status) {
    case 0:
        rc = peer_svc_add(peer, service);
        break;

    case BLE_HS_EDONE:
        /* All services discovered; start discovering characteristics. */
        if (peer->disc_prev_chr_val > 0) {
            peer_disc_chrs(peer);
        }
        rc = 0;
        break;

    default:
        rc = error->status;
        break;
    }

    if (rc != 0) {
        /* Error; abort discovery. */
        peer_disc_complete(peer, rc);
    }

    return rc;
}