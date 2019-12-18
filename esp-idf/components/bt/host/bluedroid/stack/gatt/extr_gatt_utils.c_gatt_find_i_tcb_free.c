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
struct TYPE_3__ {int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 size_t GATT_INDEX_INVALID ; 
 size_t GATT_MAX_PHY_CHANNEL ; 
 TYPE_2__ gatt_cb ; 

UINT8 gatt_find_i_tcb_free(void)
{
    UINT8 i = 0, j = GATT_INDEX_INVALID;

    for (i = 0; i < GATT_MAX_PHY_CHANNEL; i ++) {
        if (!gatt_cb.tcb[i].in_use) {
            j = i;
            break;
        }
    }
    return j;
}