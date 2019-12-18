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
struct TYPE_3__ {int sec_flags; int /*<<< orphan*/  link_key_type; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  tBTM_LINK_KEY_TYPE ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_LKEY_TYPE_IGNORE ; 
 int BTM_SEC_LINK_KEY_KNOWN ; 
 TYPE_1__* btm_find_dev (int /*<<< orphan*/ ) ; 

tBTM_LINK_KEY_TYPE BTM_SecGetDeviceLinkKeyType (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (bd_addr);

    if ((p_dev_rec != NULL) && (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN)) {
        return p_dev_rec->link_key_type;
    }
    return BTM_LKEY_TYPE_IGNORE;
}