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
struct TYPE_4__ {int /*<<< orphan*/  in_use; } ;
typedef  TYPE_1__ tGATT_REG ;
typedef  int /*<<< orphan*/  tGATT_IF ;
typedef  int UINT8 ;
struct TYPE_5__ {TYPE_1__* cl_rcb; } ;

/* Variables and functions */
 int GATT_MAX_APPS ; 
 int /*<<< orphan*/  GATT_TRACE_WARNING (char*,...) ; 
 TYPE_3__ gatt_cb ; 

tGATT_REG *gatt_get_regcb (tGATT_IF gatt_if)
{
    UINT8           ii = (UINT8)gatt_if;
    tGATT_REG       *p_reg = NULL;

    if (ii < 1 || ii > GATT_MAX_APPS) {
        GATT_TRACE_WARNING("gatt_if out of range [ = %d]", ii);
        return NULL;
    }

    // Index for cl_rcb is always 1 less than gatt_if.
    p_reg = &gatt_cb.cl_rcb[ii - 1];

    if (!p_reg->in_use) {
        GATT_TRACE_WARNING("gatt_if found but not in use.\n");
        return NULL;
    }

    return p_reg;
}