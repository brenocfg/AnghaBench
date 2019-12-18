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
struct ble_gatt_svc {int /*<<< orphan*/  start_handle; } ;
struct peer_svc {int /*<<< orphan*/  chrs; struct ble_gatt_svc svc; } ;
struct peer {int /*<<< orphan*/  svcs; } ;

/* Variables and functions */
 int BLE_HS_ENOMEM ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_AFTER (struct peer_svc*,struct peer_svc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct peer_svc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct peer_svc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 struct peer_svc* os_memblock_get (int /*<<< orphan*/ *) ; 
 struct peer_svc* peer_svc_find (struct peer*,int /*<<< orphan*/ ,struct peer_svc**) ; 
 int /*<<< orphan*/  peer_svc_pool ; 

__attribute__((used)) static int
peer_svc_add(struct peer *peer, const struct ble_gatt_svc *gatt_svc)
{
    struct peer_svc *prev;
    struct peer_svc *svc;

    svc = peer_svc_find(peer, gatt_svc->start_handle, &prev);
    if (svc != NULL) {
        /* Service already discovered. */
        return 0;
    }

    svc = os_memblock_get(&peer_svc_pool);
    if (svc == NULL) {
        /* Out of memory. */
        return BLE_HS_ENOMEM;
    }
    memset(svc, 0, sizeof * svc);

    svc->svc = *gatt_svc;
    SLIST_INIT(&svc->chrs);

    if (prev == NULL) {
        SLIST_INSERT_HEAD(&peer->svcs, svc, next);
    } else {
        SLIST_INSERT_AFTER(prev, svc, next);
    }

    return 0;
}