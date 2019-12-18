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
struct tcq_if {int tif_maxpri; int /*<<< orphan*/  tif_ifq; struct tcq_class** tif_classes; } ;
struct tcq_class {int /*<<< orphan*/  cl_q; } ;

/* Variables and functions */
 scalar_t__ IFCQ_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  qempty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcq_purgeq (struct tcq_if*,struct tcq_class*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
tcq_purge(struct tcq_if *tif)
{
	struct tcq_class *cl;
	int pri;

	IFCQ_LOCK_ASSERT_HELD(tif->tif_ifq);

	for (pri = 0; pri <= tif->tif_maxpri; pri++) {
		if ((cl = tif->tif_classes[pri]) != NULL && !qempty(&cl->cl_q))
			tcq_purgeq(tif, cl, 0, NULL, NULL);
	}
	VERIFY(IFCQ_LEN(tif->tif_ifq) == 0);
}