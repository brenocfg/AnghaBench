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
typedef  int /*<<< orphan*/  u_int32_t ;
struct tcq_if {int /*<<< orphan*/  tif_ifq; } ;
struct tcq_class {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 int tcq_class_destroy (struct tcq_if*,struct tcq_class*) ; 
 struct tcq_class* tcq_clh_to_clp (struct tcq_if*,int /*<<< orphan*/ ) ; 

int
tcq_remove_queue(struct tcq_if *tif, u_int32_t qid)
{
	struct tcq_class *cl;

	IFCQ_LOCK_ASSERT_HELD(tif->tif_ifq);

	if ((cl = tcq_clh_to_clp(tif, qid)) == NULL)
		return (EINVAL);

	return (tcq_class_destroy(tif, cl));
}