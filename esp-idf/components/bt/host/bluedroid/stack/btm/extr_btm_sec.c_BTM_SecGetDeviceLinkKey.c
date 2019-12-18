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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_3__ {int sec_flags; int /*<<< orphan*/  link_key; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  LINK_KEY ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int BTM_SEC_LINK_KEY_KNOWN ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 int /*<<< orphan*/  LINK_KEY_LEN ; 
 TYPE_1__* btm_find_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tBTM_STATUS BTM_SecGetDeviceLinkKey (BD_ADDR bd_addr, LINK_KEY link_key)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if (((p_dev_rec = btm_find_dev (bd_addr)) != NULL)
            && (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN)) {
        memcpy (link_key, p_dev_rec->link_key, LINK_KEY_LEN);
        return (BTM_SUCCESS);
    }
    return (BTM_UNKNOWN_ADDR);
}