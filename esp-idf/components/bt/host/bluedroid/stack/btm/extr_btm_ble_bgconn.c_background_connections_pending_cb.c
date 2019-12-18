#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* data; } ;
typedef  TYPE_2__ hash_map_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  address; } ;
struct TYPE_7__ {TYPE_1__ address; } ;
typedef  TYPE_3__ background_connection_t ;

/* Variables and functions */
 int BTM_IsAclConnectionUp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 

__attribute__((used)) static bool background_connections_pending_cb(hash_map_entry_t *hash_entry, void *context)
{
    bool *pending_connections = context;
    background_connection_t *connection = hash_entry->data;
    const bool connected = BTM_IsAclConnectionUp(connection->address.address, BT_TRANSPORT_LE);
    if (!connected) {
        *pending_connections = true;
        return false;
    }
    return true;
}