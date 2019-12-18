#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; size_t hci_handle; } ;
typedef  TYPE_2__ tSCO_CONN ;
typedef  size_t UINT16 ;
struct TYPE_4__ {TYPE_2__* sco_db; } ;
struct TYPE_6__ {TYPE_1__ sco_cb; } ;

/* Variables and functions */
 size_t BTM_INVALID_HCI_HANDLE ; 
 size_t BTM_MAX_SCO_LINKS ; 
 scalar_t__ SCO_ST_CONNECTED ; 
 TYPE_3__ btm_cb ; 

UINT16 BTM_ReadScoHandle (UINT16 sco_inx)
{
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CONN   *p = &btm_cb.sco_cb.sco_db[sco_inx];

    /* Validity check */
    if ((sco_inx < BTM_MAX_SCO_LINKS) && (p->state == SCO_ST_CONNECTED)) {
        return (p->hci_handle);
    } else {
        return (BTM_INVALID_HCI_HANDLE);
    }
#else
    return (BTM_INVALID_HCI_HANDLE);
#endif
}