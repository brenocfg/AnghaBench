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
typedef  void* u32 ;
struct dc390_srb {void* SGToBeXferLen; unsigned long SGBusAddr; unsigned long TotalXferredLen; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long inline dc390_advance_segment(struct dc390_srb* pSRB, u32 residue)
{
	unsigned long xfer = pSRB->SGToBeXferLen - residue;

	/* xfer more bytes transferred */
	pSRB->SGBusAddr += xfer;
	pSRB->TotalXferredLen += xfer;
	pSRB->SGToBeXferLen = residue;

	return xfer;
}