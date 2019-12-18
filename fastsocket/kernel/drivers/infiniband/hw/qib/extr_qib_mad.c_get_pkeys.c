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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qib_pportdata {size_t hw_pidx; } ;
struct qib_devdata {struct qib_ctxtdata** rcd; struct qib_pportdata* pport; } ;
struct qib_ctxtdata {int /*<<< orphan*/  pkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_pkeys(struct qib_devdata *dd, u8 port, u16 *pkeys)
{
	struct qib_pportdata *ppd = dd->pport + port - 1;
	/*
	 * always a kernel context, no locking needed.
	 * If we get here with ppd setup, no need to check
	 * that pd is valid.
	 */
	struct qib_ctxtdata *rcd = dd->rcd[ppd->hw_pidx];

	memcpy(pkeys, rcd->pkeys, sizeof(rcd->pkeys));

	return 0;
}