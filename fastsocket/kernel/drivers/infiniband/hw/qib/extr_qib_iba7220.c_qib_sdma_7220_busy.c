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
typedef  int u64 ;
struct qib_pportdata {int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AbortInProg ; 
 int /*<<< orphan*/  InternalSDmaEnable ; 
 int SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScbEmpty ; 
 int /*<<< orphan*/  ScoreBoardDrainInProg ; 
 int /*<<< orphan*/  SendDmaStatus ; 
 int /*<<< orphan*/  kr_senddmastatus ; 
 int qib_read_kreg64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_sdma_7220_busy(struct qib_pportdata *ppd)
{
	u64 hwstatus = qib_read_kreg64(ppd->dd, kr_senddmastatus);

	return (hwstatus & SYM_MASK(SendDmaStatus, ScoreBoardDrainInProg)) ||
	       (hwstatus & SYM_MASK(SendDmaStatus, AbortInProg)) ||
	       (hwstatus & SYM_MASK(SendDmaStatus, InternalSDmaEnable)) ||
	       !(hwstatus & SYM_MASK(SendDmaStatus, ScbEmpty));
}