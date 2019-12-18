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
struct peer {int /*<<< orphan*/  conn_handle; } ;

/* Variables and functions */
 int BLE_HS_EALREADY ; 
 int BLE_HS_ENOMEM ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct peer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 struct peer* os_memblock_get (int /*<<< orphan*/ *) ; 
 struct peer* peer_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peer_pool ; 
 int /*<<< orphan*/  peers ; 

int
peer_add(uint16_t conn_handle)
{
    struct peer *peer;

    /* Make sure the connection handle is unique. */
    peer = peer_find(conn_handle);
    if (peer != NULL) {
        return BLE_HS_EALREADY;
    }

    peer = os_memblock_get(&peer_pool);
    if (peer == NULL) {
        /* Out of memory. */
        return BLE_HS_ENOMEM;
    }

    memset(peer, 0, sizeof * peer);
    peer->conn_handle = conn_handle;

    SLIST_INSERT_HEAD(&peers, peer, next);

    return 0;
}