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
struct dc390_srb {int TagNumber; } ;
struct dc390_dcb {int TagMask; } ;

/* Variables and functions */
 int SCSI_NO_TAG ; 

__attribute__((used)) static void __inline__
dc390_freetag (struct dc390_dcb* pDCB, struct dc390_srb* pSRB)
{
	if (pSRB->TagNumber != SCSI_NO_TAG) {
		pDCB->TagMask &= ~(1 << pSRB->TagNumber);   /* free tag mask */
		pSRB->TagNumber = SCSI_NO_TAG;
	}
}