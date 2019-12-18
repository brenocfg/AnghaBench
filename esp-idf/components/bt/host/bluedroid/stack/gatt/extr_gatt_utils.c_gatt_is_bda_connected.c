#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT8 ;
struct TYPE_4__ {TYPE_1__* tcb; } ;
struct TYPE_3__ {int /*<<< orphan*/  peer_bda; scalar_t__ in_use; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 size_t GATT_MAX_PHY_CHANNEL ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ gatt_cb ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN gatt_is_bda_connected(BD_ADDR bda)
{
    UINT8 i = 0;
    BOOLEAN connected = FALSE;

    for ( i = 0; i < GATT_MAX_PHY_CHANNEL; i ++) {
        if (gatt_cb.tcb[i].in_use &&
                !memcmp(gatt_cb.tcb[i].peer_bda, bda, BD_ADDR_LEN)) {
            connected = TRUE;
            break;
        }
    }
    return connected;
}