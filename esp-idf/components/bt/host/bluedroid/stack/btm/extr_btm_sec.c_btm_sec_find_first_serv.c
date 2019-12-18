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
struct TYPE_4__ {scalar_t__ psm; int security_flags; } ;
typedef  TYPE_1__ tBTM_SEC_SERV_REC ;
typedef  scalar_t__ UINT16 ;
struct TYPE_5__ {TYPE_1__* p_out_serv; TYPE_1__* sec_serv_rec; } ;
typedef  int CONNECTION_TYPE ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int BTM_SEC_IN_USE ; 
 int BTM_SEC_MAX_SERVICE_RECORDS ; 
 int CONNECTION_TYPE_ORIG_MASK ; 
 int FALSE ; 
 int TRUE ; 
 TYPE_3__ btm_cb ; 

tBTM_SEC_SERV_REC *btm_sec_find_first_serv (CONNECTION_TYPE conn_type, UINT16 psm)
{
    tBTM_SEC_SERV_REC *p_serv_rec = &btm_cb.sec_serv_rec[0];
    int i;
    BOOLEAN is_originator;

#if (L2CAP_UCD_INCLUDED == TRUE)

    if ( conn_type & CONNECTION_TYPE_ORIG_MASK ) {
        is_originator = TRUE;
    } else {
        is_originator = FALSE;
    }
#else
    is_originator = conn_type;
#endif

    if (is_originator && btm_cb.p_out_serv && btm_cb.p_out_serv->psm == psm) {
        /* If this is outgoing connection and the PSM matches p_out_serv,
         * use it as the current service */
        return btm_cb.p_out_serv;
    }

    /* otherwise, just find the first record with the specified PSM */
    for (i = 0; i < BTM_SEC_MAX_SERVICE_RECORDS; i++, p_serv_rec++) {
        if ( (p_serv_rec->security_flags & BTM_SEC_IN_USE) && (p_serv_rec->psm == psm) ) {
            return (p_serv_rec);
        }
    }
    return (NULL);
}