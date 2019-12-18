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
typedef  int /*<<< orphan*/  uchar ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 scalar_t__ AscHostReqRiscHalt (int /*<<< orphan*/ ) ; 
 int AscSetChipSynRegAtID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscStartChip (int /*<<< orphan*/ ) ; 
 int FALSE ; 

__attribute__((used)) static int
AscSetRunChipSynRegAtID(PortAddr iop_base, uchar tid_no, uchar sdtr_data)
{
	int sta = FALSE;

	if (AscHostReqRiscHalt(iop_base)) {
		sta = AscSetChipSynRegAtID(iop_base, tid_no, sdtr_data);
		AscStartChip(iop_base);
	}
	return sta;
}