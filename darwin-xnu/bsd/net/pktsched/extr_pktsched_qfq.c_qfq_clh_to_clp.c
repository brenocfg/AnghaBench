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
typedef  int u_int32_t ;
struct qfq_if {int qif_maxclasses; struct qfq_class** qif_class_tbl; int /*<<< orphan*/  qif_ifq; } ;
struct qfq_class {int cl_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct qfq_class *
qfq_clh_to_clp(struct qfq_if *qif, u_int32_t chandle)
{
	struct qfq_class *cl;
	int i;

	IFCQ_LOCK_ASSERT_HELD(qif->qif_ifq);

	/*
	 * First, try optimistically the slot matching the lower bits of
	 * the handle.  If it fails, do the linear table search.
	 */
	i = chandle % qif->qif_maxclasses;
	if ((cl = qif->qif_class_tbl[i]) != NULL && cl->cl_handle == chandle)
		return (cl);
	for (i = 0; i < qif->qif_maxclasses; i++)
		if ((cl = qif->qif_class_tbl[i]) != NULL &&
		    cl->cl_handle == chandle)
			return (cl);

	return (NULL);
}