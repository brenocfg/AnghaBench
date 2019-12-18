#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_6__ {TYPE_1__* srv_list; TYPE_2__* sr_reg; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_hdl; } ;
struct TYPE_4__ {size_t i_sreg; int /*<<< orphan*/  is_primary; int /*<<< orphan*/  s_hdl; int /*<<< orphan*/  in_use; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 TYPE_3__ gatt_cb ; 

void gatts_update_srv_list_elem(UINT8 i_sreg, UINT16 handle, BOOLEAN is_primary)
{
    UNUSED(handle);

    gatt_cb.srv_list[i_sreg].in_use         = TRUE;
    gatt_cb.srv_list[i_sreg].i_sreg    = i_sreg;
    gatt_cb.srv_list[i_sreg].s_hdl          = gatt_cb.sr_reg[i_sreg].s_hdl;
    gatt_cb.srv_list[i_sreg].is_primary     = is_primary;

    return;
}