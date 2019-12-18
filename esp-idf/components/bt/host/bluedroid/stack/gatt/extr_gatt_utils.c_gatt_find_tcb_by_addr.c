#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  size_t UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/ * tcb; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 size_t GATT_INDEX_INVALID ; 
 TYPE_1__ gatt_cb ; 
 size_t gatt_find_i_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tGATT_TCB *gatt_find_tcb_by_addr(BD_ADDR bda, tBT_TRANSPORT transport)
{
    tGATT_TCB   *p_tcb = NULL;
    UINT8 i = 0;

    if ((i = gatt_find_i_tcb_by_addr(bda, transport)) != GATT_INDEX_INVALID) {
        p_tcb = &gatt_cb.tcb[i];
    }

    return p_tcb;
}