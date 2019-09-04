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
typedef  scalar_t__ u_int32_t ;
struct tcq_if {int tif_maxpri; struct tcq_class** tif_classes; int /*<<< orphan*/  tif_ifq; } ;
struct tcq_class {scalar_t__ cl_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct tcq_class *
tcq_clh_to_clp(struct tcq_if *tif, u_int32_t chandle)
{
	struct tcq_class *cl;
	int idx;

	IFCQ_LOCK_ASSERT_HELD(tif->tif_ifq);

	for (idx = tif->tif_maxpri; idx >= 0; idx--)
		if ((cl = tif->tif_classes[idx]) != NULL &&
		    cl->cl_handle == chandle)
			return (cl);

	return (NULL);
}