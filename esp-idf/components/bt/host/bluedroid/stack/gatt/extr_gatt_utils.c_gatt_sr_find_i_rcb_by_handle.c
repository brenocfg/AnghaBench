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
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {TYPE_1__* sr_reg; } ;
struct TYPE_3__ {scalar_t__ s_hdl; scalar_t__ e_hdl; scalar_t__ in_use; } ;

/* Variables and functions */
 size_t GATT_MAX_SR_PROFILES ; 
 TYPE_2__ gatt_cb ; 

UINT8 gatt_sr_find_i_rcb_by_handle(UINT16 handle)
{
    UINT8  i_rcb = 0;

    for ( ; i_rcb < GATT_MAX_SR_PROFILES; i_rcb++) {
        if (gatt_cb.sr_reg[i_rcb].in_use &&
                gatt_cb.sr_reg[i_rcb].s_hdl <= handle &&
                gatt_cb.sr_reg[i_rcb].e_hdl >= handle ) {
            break;
        }
    }
    return i_rcb;
}