#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tGATT_IF ;
struct TYPE_3__ {scalar_t__* gatt_if; } ;
typedef  TYPE_1__ tGATT_BG_CONN_DEV ;
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t GATT_MAX_APPS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* gatt_find_bg_dev (int /*<<< orphan*/ ) ; 

BOOLEAN gatt_find_app_for_bg_dev(BD_ADDR bd_addr, tGATT_IF *p_gatt_if)
{
    tGATT_BG_CONN_DEV   *p_dev = NULL;
    UINT8   i;
    BOOLEAN ret = FALSE;

    if ((p_dev = gatt_find_bg_dev(bd_addr)) == NULL) {
        return ret;
    }

    for (i = 0; i < GATT_MAX_APPS; i ++) {
        if (p_dev->gatt_if[i] != 0 ) {
            *p_gatt_if = p_dev->gatt_if[i];
            ret = TRUE;
            break;
        }
    }
    return ret;
}