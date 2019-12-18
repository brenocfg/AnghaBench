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
struct TYPE_4__ {scalar_t__ hci_handle; scalar_t__ in_use; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_5__ {TYPE_1__* acl_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 scalar_t__ MAX_L2CAP_LINKS ; 
 TYPE_3__ btm_cb ; 

tACL_CONN *btm_handle_to_acl (UINT16 hci_handle)
{
    tACL_CONN   *p = &btm_cb.acl_db[0];
    UINT8       xx;
    BTM_TRACE_DEBUG ("btm_handle_to_acl_index\n");
    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p++) {
        if ((p->in_use) && (p->hci_handle == hci_handle)) {
            return(p);
        }
    }

    /* If here, no BD Addr found */
    return ((tACL_CONN *)NULL);
}