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
struct qib_pportdata {int /*<<< orphan*/  guid; } ;
struct qib_ibport {int /*<<< orphan*/ * guids; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 

__attribute__((used)) static __be64 get_sguid(struct qib_ibport *ibp, unsigned index)
{
	if (!index) {
		struct qib_pportdata *ppd = ppd_from_ibp(ibp);

		return ppd->guid;
	} else
		return ibp->guids[index - 1];
}