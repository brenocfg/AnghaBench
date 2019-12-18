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
typedef  int /*<<< orphan*/  bt_bdaddr_t ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ background_connections ; 
 int /*<<< orphan*/  hash_map_erase (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOLEAN background_connection_remove(bt_bdaddr_t *address)
{
    if (address && background_connections) {
        return hash_map_erase(background_connections, address);
    }
    return FALSE;
}