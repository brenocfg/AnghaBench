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
struct TYPE_3__ {int /*<<< orphan*/  is_flushable; } ;
typedef  TYPE_1__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* l2cu_find_ccb_by_cid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOLEAN L2CA_SetChnlFlushability (UINT16 cid, BOOLEAN is_flushable)
{
#if (L2CAP_NON_FLUSHABLE_PB_INCLUDED == TRUE)

    tL2C_CCB        *p_ccb;

    /* Find the channel control block. We don't know the link it is on. */
    if ((p_ccb = l2cu_find_ccb_by_cid (NULL, cid)) == NULL) {
        L2CAP_TRACE_WARNING ("L2CAP - no CCB for L2CA_SetChnlFlushability, CID: %d", cid);
        return (FALSE);
    }

    p_ccb->is_flushable = is_flushable;

    L2CAP_TRACE_API ("L2CA_SetChnlFlushability()  CID: 0x%04x  is_flushable: %d", cid, is_flushable);

#endif

    return (TRUE);
}