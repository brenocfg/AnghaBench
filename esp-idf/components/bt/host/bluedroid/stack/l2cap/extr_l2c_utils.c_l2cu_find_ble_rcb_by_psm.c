#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ psm; scalar_t__ in_use; } ;
typedef  TYPE_1__ tL2C_RCB ;
typedef  scalar_t__ UINT16 ;
struct TYPE_5__ {TYPE_1__* ble_rcb_pool; } ;

/* Variables and functions */
 scalar_t__ BLE_MAX_L2CAP_CLIENTS ; 
 TYPE_3__ l2cb ; 

tL2C_RCB *l2cu_find_ble_rcb_by_psm (UINT16 psm)
{
    tL2C_RCB    *p_rcb = &l2cb.ble_rcb_pool[0];
    UINT16      xx;

    for (xx = 0; xx < BLE_MAX_L2CAP_CLIENTS; xx++, p_rcb++)
    {
        if ((p_rcb->in_use) && (p_rcb->psm == psm)) {
            return (p_rcb);
        }
    }

    /* If here, no match found */
    return (NULL);
}