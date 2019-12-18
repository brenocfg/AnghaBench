#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bt_bdaddr_t ;
struct TYPE_5__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ background_connection_t ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  background_connections ; 
 int /*<<< orphan*/  background_connections_lazy_init () ; 
 TYPE_1__* hash_map_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_map_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* osi_calloc (int) ; 

__attribute__((used)) static BOOLEAN background_connection_add(bt_bdaddr_t *address)
{
    assert(address);
    background_connections_lazy_init();
    background_connection_t *connection = hash_map_get(background_connections, address);
    if (!connection) {
        connection = osi_calloc(sizeof(background_connection_t));
        connection->address = *address;
        hash_map_set(background_connections, &(connection->address), connection);
        return TRUE;
    }
    return FALSE;
}