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
struct TYPE_3__ {int device_type; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int BT_DEVICE_TYPE_BLE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* btm_find_dev (int /*<<< orphan*/ ) ; 

BOOLEAN btm_sec_is_le_capable_dev (BD_ADDR bda)
{
    BOOLEAN le_capable = FALSE;

#if (BLE_INCLUDED== TRUE)
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (bda);
    if (p_dev_rec && (p_dev_rec->device_type & BT_DEVICE_TYPE_BLE) == BT_DEVICE_TYPE_BLE) {
        le_capable  = TRUE;
    }
#endif
    return le_capable;
}