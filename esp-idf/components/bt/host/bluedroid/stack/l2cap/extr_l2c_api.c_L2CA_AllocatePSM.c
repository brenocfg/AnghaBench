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
typedef  int UINT16 ;
struct TYPE_2__ {int dyn_psm; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int BRCM_RESERVED_PSM_END ; 
 int BRCM_RESERVED_PSM_START ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 TYPE_1__ l2cb ; 
 int /*<<< orphan*/ * l2cu_find_rcb_by_psm (int) ; 

UINT16 L2CA_AllocatePSM(void)
{
    BOOLEAN done = FALSE;
    UINT16 psm = l2cb.dyn_psm;

    while (!done) {
        psm += 2;
        if (psm > 0xfeff) {
            psm = 0x1001;
        } else if (psm & 0x0100) {
            /* the upper byte must be even */
            psm += 0x0100;
        }

        /* if psm is in range of reserved BRCM Aware features */
        if ((BRCM_RESERVED_PSM_START <= psm) && (psm <= BRCM_RESERVED_PSM_END)) {
            continue;
        }

        /* make sure the newlly allocated psm is not used right now */
        if ((l2cu_find_rcb_by_psm (psm)) == NULL) {
            done = TRUE;
        }
    }
    l2cb.dyn_psm = psm;

    return (psm);
}