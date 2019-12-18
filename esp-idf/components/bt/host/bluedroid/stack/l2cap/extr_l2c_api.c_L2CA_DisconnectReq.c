#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CEVT_L2CA_DISCONNECT_REQ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  l2c_csm_execute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * l2cu_find_ccb_by_cid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOLEAN L2CA_DisconnectReq (UINT16 cid)
{
    tL2C_CCB        *p_ccb;

    //counter_add("l2cap.disconn.req", 1);
    L2CAP_TRACE_API ("L2CA_DisconnectReq()  CID: 0x%04x", cid);

    /* Find the channel control block. We don't know the link it is on. */
    if ((p_ccb = l2cu_find_ccb_by_cid (NULL, cid)) == NULL) {
        L2CAP_TRACE_WARNING ("L2CAP - no CCB for L2CA_disc_req, CID: %d", cid);
        return (FALSE);
    }

    l2c_csm_execute (p_ccb, L2CEVT_L2CA_DISCONNECT_REQ, NULL);

    return (TRUE);
}