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
typedef  int tBTA_SYS_HW_MODULE ;
struct TYPE_4__ {scalar_t__* is_reg; TYPE_1__** reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int) ; 
 int /*<<< orphan*/  APPL_TRACE_WARNING (char*) ; 
 int BTA_ID_BLUETOOTH_MAX ; 
 int BTA_ID_DM ; 
#define  BTA_SYS_HW_BLUETOOTH 128 
 scalar_t__ TRUE ; 
 TYPE_2__ bta_sys_cb ; 
 int /*<<< orphan*/  stub1 () ; 

void bta_sys_disable(tBTA_SYS_HW_MODULE module)
{
    int bta_id = 0;
    int bta_id_max = 0;

    APPL_TRACE_DEBUG("bta_sys_disable: module %i", module);

    switch ( module ) {
    case BTA_SYS_HW_BLUETOOTH:
        bta_id = BTA_ID_DM;
        bta_id_max = BTA_ID_BLUETOOTH_MAX;
        break;
    default:
        APPL_TRACE_WARNING("bta_sys_disable: unkown module");
        return;
    }

    for ( ; bta_id <= bta_id_max; bta_id++) {
        if (bta_sys_cb.reg[bta_id] != NULL) {
            if (bta_sys_cb.is_reg[bta_id] == TRUE  &&  bta_sys_cb.reg[bta_id]->disable != NULL) {
                (*bta_sys_cb.reg[bta_id]->disable)();
            }
        }
    }
}