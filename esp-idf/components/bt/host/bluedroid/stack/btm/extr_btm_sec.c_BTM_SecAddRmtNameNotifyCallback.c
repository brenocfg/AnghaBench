#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_RMT_NAME_CALLBACK ;
struct TYPE_2__ {int /*<<< orphan*/ ** p_rmt_name_callback; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int BTM_SEC_MAX_RMT_NAME_CALLBACKS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ btm_cb ; 

BOOLEAN  BTM_SecAddRmtNameNotifyCallback (tBTM_RMT_NAME_CALLBACK *p_callback)
{
    int i;

    for (i = 0; i < BTM_SEC_MAX_RMT_NAME_CALLBACKS; i++) {
        if (btm_cb.p_rmt_name_callback[i] == NULL) {
            btm_cb.p_rmt_name_callback[i] = p_callback;
            return (TRUE);
        }
    }
    return (FALSE);
}