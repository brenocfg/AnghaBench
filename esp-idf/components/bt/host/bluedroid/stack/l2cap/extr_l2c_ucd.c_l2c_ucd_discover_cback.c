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
struct TYPE_5__ {int /*<<< orphan*/  (* pL2CA_UCD_Discover_Cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int state; TYPE_1__ cb_info; } ;
struct TYPE_7__ {TYPE_2__ ucd; scalar_t__ in_use; } ;
typedef  TYPE_3__ tL2C_RCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_8__ {TYPE_3__* rcb_pool; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  L2CAP_UCD_INFO_TYPE_MTU ; 
 int /*<<< orphan*/  L2CAP_UCD_INFO_TYPE_RECEPTION ; 
 int L2C_UCD_STATE_W4_MTU ; 
 int L2C_UCD_STATE_W4_RECEPTION ; 
 scalar_t__ MAX_L2CAP_CLIENTS ; 
 TYPE_4__ l2cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2c_ucd_discover_cback (BD_ADDR rem_bda, UINT8 info_type, UINT32 data)
{
    tL2C_RCB    *p_rcb = &l2cb.rcb_pool[0];
    UINT16      xx;

    L2CAP_TRACE_DEBUG ("L2CAP - l2c_ucd_discover_cback");

    for (xx = 0; xx < MAX_L2CAP_CLIENTS; xx++, p_rcb++) {
        if (p_rcb->in_use) {
            /* if this application is waiting UCD reception info */
            if (( info_type == L2CAP_UCD_INFO_TYPE_RECEPTION )
                    && ( p_rcb->ucd.state & L2C_UCD_STATE_W4_RECEPTION )) {
                p_rcb->ucd.cb_info.pL2CA_UCD_Discover_Cb (rem_bda, info_type, data);
                p_rcb->ucd.state &= ~(L2C_UCD_STATE_W4_RECEPTION);
            }

            /* if this application is waiting UCD MTU info */
            if (( info_type == L2CAP_UCD_INFO_TYPE_MTU )
                    && ( p_rcb->ucd.state & L2C_UCD_STATE_W4_MTU )) {
                p_rcb->ucd.cb_info.pL2CA_UCD_Discover_Cb (rem_bda, info_type, data);
                p_rcb->ucd.state &= ~(L2C_UCD_STATE_W4_MTU);
            }
        }
    }
}