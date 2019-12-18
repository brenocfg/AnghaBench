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
struct qib_pportdata {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QIB_IB_TBL_VL_HIGH_ARB 129 
#define  QIB_IB_TBL_VL_LOW_ARB 128 
 int /*<<< orphan*/  get_vl_weights (struct qib_pportdata*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  krp_highprio_0 ; 
 int /*<<< orphan*/  krp_lowprio_0 ; 

__attribute__((used)) static int qib_7322_get_ib_table(struct qib_pportdata *ppd, int which, void *t)
{
	switch (which) {
	case QIB_IB_TBL_VL_HIGH_ARB:
		get_vl_weights(ppd, krp_highprio_0, t);
		break;

	case QIB_IB_TBL_VL_LOW_ARB:
		get_vl_weights(ppd, krp_lowprio_0, t);
		break;

	default:
		return -EINVAL;
	}
	return 0;
}