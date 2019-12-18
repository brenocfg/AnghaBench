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
struct TYPE_3__ {int security_flags; scalar_t__ psm; scalar_t__ service_id; scalar_t__ ucd_security_flags; } ;
typedef  TYPE_1__ tBTM_SEC_SERV_REC ;
typedef  scalar_t__ UINT8 ;
struct TYPE_4__ {TYPE_1__* sec_serv_rec; } ;

/* Variables and functions */
 int BTM_SEC_IN_USE ; 
 int BTM_SEC_MAX_SERVICE_RECORDS ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,int,scalar_t__) ; 
 scalar_t__ BT_PSM_SDP ; 
 TYPE_2__ btm_cb ; 

UINT8 BTM_SecClrService (UINT8 service_id)
{
    tBTM_SEC_SERV_REC   *p_srec = &btm_cb.sec_serv_rec[0];
    UINT8   num_freed = 0;
    int     i;

    for (i = 0; i < BTM_SEC_MAX_SERVICE_RECORDS; i++, p_srec++) {
        /* Delete services with specified name (if in use and not SDP) */
        if ((p_srec->security_flags & BTM_SEC_IN_USE) && (p_srec->psm != BT_PSM_SDP) &&
                (!service_id || (service_id == p_srec->service_id))) {
            BTM_TRACE_API("BTM_SEC_CLR[%d]: id %d\n", i, service_id);
            p_srec->security_flags = 0;
#if (L2CAP_UCD_INCLUDED == TRUE)
            p_srec->ucd_security_flags = 0;
#endif
            num_freed++;
        }
    }

    return (num_freed);
}