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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
struct TYPE_3__ {int /*<<< orphan*/ * p_stored_link_key_cmpl_cb; } ;
struct TYPE_4__ {TYPE_1__ devcb; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BUSY ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,char*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_delete_stored_key (int /*<<< orphan*/ ,scalar_t__) ; 

tBTM_STATUS BTM_DeleteStoredLinkKey(BD_ADDR bd_addr, tBTM_CMPL_CB *p_cb)
{
    BD_ADDR local_bd_addr;
    BOOLEAN delete_all_flag = FALSE;

    /* Check if the previous command is completed */
    if (btm_cb.devcb.p_stored_link_key_cmpl_cb) {
        return (BTM_BUSY);
    }

    if (!bd_addr) {
        /* This is to delete all link keys */
        delete_all_flag = TRUE;

        /* We don't care the BD address. Just pass a non zero pointer */
        bd_addr = local_bd_addr;
    }

    BTM_TRACE_EVENT ("BTM: BTM_DeleteStoredLinkKey: delete_all_flag: %s",
                     delete_all_flag ? "TRUE" : "FALSE");

    /* Send the HCI command */
    btm_cb.devcb.p_stored_link_key_cmpl_cb = p_cb;
    if (!btsnd_hcic_delete_stored_key (bd_addr, delete_all_flag)) {
        return (BTM_NO_RESOURCES);
    } else {
        return (BTM_SUCCESS);
    }
}