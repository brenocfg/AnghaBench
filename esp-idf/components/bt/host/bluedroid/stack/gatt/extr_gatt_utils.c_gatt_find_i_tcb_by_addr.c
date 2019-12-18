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
typedef  scalar_t__ tBT_TRANSPORT ;
typedef  size_t UINT8 ;
struct TYPE_4__ {TYPE_1__* tcb; } ;
struct TYPE_3__ {scalar_t__ transport; int /*<<< orphan*/  peer_bda; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 size_t GATT_INDEX_INVALID ; 
 size_t GATT_MAX_PHY_CHANNEL ; 
 TYPE_2__ gatt_cb ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT8 gatt_find_i_tcb_by_addr(BD_ADDR bda, tBT_TRANSPORT transport)
{
    UINT8 i = 0;

    for ( ; i < GATT_MAX_PHY_CHANNEL; i ++) {
        if (!memcmp(gatt_cb.tcb[i].peer_bda, bda, BD_ADDR_LEN) &&
                gatt_cb.tcb[i].transport == transport) {
            return i;
        }
    }
    return GATT_INDEX_INVALID;
}