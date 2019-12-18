#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ interval; } ;
typedef  TYPE_2__ tBTM_PM_MCB ;
struct TYPE_7__ {int /*<<< orphan*/  remote_addr; } ;
typedef  TYPE_3__ tACL_CONN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_8__ {TYPE_1__* pm_reg_db; TYPE_3__* acl_db; TYPE_2__* pm_mode_db; } ;
struct TYPE_5__ {int mask; int /*<<< orphan*/  (* cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BTM_MAX_PM_RECORDS ; 
 int BTM_PM_REG_NOTIF ; 
 int /*<<< orphan*/  BTM_PM_STS_SSR ; 
 scalar_t__ FALSE ; 
 int MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UNUSED (scalar_t__) ; 
 TYPE_4__ btm_cb ; 
 int btm_handle_to_acl_index (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void btm_pm_proc_ssr_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8       status;
    UINT16      handle;
    UINT16      max_rx_lat;
    int         xx, yy;
    tBTM_PM_MCB *p_cb;
    tACL_CONN   *p_acl = NULL;
    UINT16      use_ssr = TRUE;
    UNUSED(evt_len);

    STREAM_TO_UINT8 (status, p);

    STREAM_TO_UINT16 (handle, p);
    /* get the index to acl_db */
    if ((xx = btm_handle_to_acl_index(handle)) >= MAX_L2CAP_LINKS) {
        return;
    }

    p += 2;
    STREAM_TO_UINT16 (max_rx_lat, p);
    p_cb = &(btm_cb.pm_mode_db[xx]);

    p_acl = &btm_cb.acl_db[xx];
    if (p_cb->interval == max_rx_lat) {
        /* using legacy sniff */
        use_ssr = FALSE;
    }

    /* notify registered parties */
    for (yy = 0; yy < BTM_MAX_PM_RECORDS; yy++) {
        if (btm_cb.pm_reg_db[yy].mask & BTM_PM_REG_NOTIF) {
            if ( p_acl) {
                (*btm_cb.pm_reg_db[yy].cback)( p_acl->remote_addr, BTM_PM_STS_SSR, use_ssr, status);
            }
        }
    }
}