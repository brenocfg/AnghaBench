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
struct TYPE_4__ {int sec_flags; scalar_t__ sec_state; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  scalar_t__ UINT8 ;
struct TYPE_5__ {TYPE_1__* sec_dev_rec; } ;

/* Variables and functions */
 int BTM_SEC_IN_USE ; 
 int BTM_SEC_MAX_DEVICE_RECORDS ; 
 TYPE_3__ btm_cb ; 

tBTM_SEC_DEV_REC *btm_sec_find_dev_by_sec_state (UINT8 state)
{
#if (SMP_INCLUDED == TRUE)
    tBTM_SEC_DEV_REC *p_dev_rec = &btm_cb.sec_dev_rec[0];

    for (int i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++) {
        if ((p_dev_rec->sec_flags & BTM_SEC_IN_USE)
                && (p_dev_rec->sec_state == state)) {
            return (p_dev_rec);
        }
    }
#endif  ///SMP_INCLUDED == TRUE
    return (NULL);
}