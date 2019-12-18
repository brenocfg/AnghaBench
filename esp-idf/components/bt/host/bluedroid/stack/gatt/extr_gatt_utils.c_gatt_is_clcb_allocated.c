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
struct TYPE_4__ {TYPE_1__* clcb; } ;
struct TYPE_3__ {scalar_t__ conn_id; scalar_t__ in_use; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t GATT_CL_MAX_LCB ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ gatt_cb ; 

BOOLEAN gatt_is_clcb_allocated (UINT16 conn_id)
{
    UINT8         i = 0;
    BOOLEAN       is_allocated = FALSE;

    for (i = 0; i < GATT_CL_MAX_LCB; i++) {
        if (gatt_cb.clcb[i].in_use && (gatt_cb.clcb[i].conn_id == conn_id)) {
            is_allocated = TRUE;
            break;
        }
    }

    return is_allocated;
}