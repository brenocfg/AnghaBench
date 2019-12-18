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
typedef  int /*<<< orphan*/  uint16_t ;
struct peer_svc {int dummy; } ;
struct peer {int /*<<< orphan*/  svcs; } ;

/* Variables and functions */
 int BLE_HS_ENOTCONN ; 
 int BLE_HS_EOS ; 
 struct peer_svc* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct peer*,struct peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int os_memblock_put (int /*<<< orphan*/ *,struct peer*) ; 
 struct peer* peer_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peer_pool ; 
 int /*<<< orphan*/  peer_svc_delete (struct peer_svc*) ; 
 int /*<<< orphan*/  peers ; 

int
peer_delete(uint16_t conn_handle)
{
    struct peer_svc *svc;
    struct peer *peer;
    int rc;

    peer = peer_find(conn_handle);
    if (peer == NULL) {
        return BLE_HS_ENOTCONN;
    }

    SLIST_REMOVE(&peers, peer, peer, next);

    while ((svc = SLIST_FIRST(&peer->svcs)) != NULL) {
        SLIST_REMOVE_HEAD(&peer->svcs, next);
        peer_svc_delete(svc);
    }

    rc = os_memblock_put(&peer_pool, peer);
    if (rc != 0) {
        return BLE_HS_EOS;
    }

    return 0;
}