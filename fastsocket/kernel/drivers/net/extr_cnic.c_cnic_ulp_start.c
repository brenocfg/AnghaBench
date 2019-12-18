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
struct cnic_ulp_ops {int /*<<< orphan*/  (* cnic_start ) (int /*<<< orphan*/ ) ;} ;
struct cnic_local {int /*<<< orphan*/ * ulp_flags; int /*<<< orphan*/ * ulp_handle; struct cnic_ulp_ops** ulp_ops; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int MAX_CNIC_ULP_TYPE ; 
 int /*<<< orphan*/  ULP_F_CALL_PENDING ; 
 int /*<<< orphan*/  ULP_F_START ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_ulp_start(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	int if_type;

	for (if_type = 0; if_type < MAX_CNIC_ULP_TYPE; if_type++) {
		struct cnic_ulp_ops *ulp_ops;

		mutex_lock(&cnic_lock);
		ulp_ops = cp->ulp_ops[if_type];
		if (!ulp_ops || !ulp_ops->cnic_start) {
			mutex_unlock(&cnic_lock);
			continue;
		}
		set_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[if_type]);
		mutex_unlock(&cnic_lock);

		if (!test_and_set_bit(ULP_F_START, &cp->ulp_flags[if_type]))
			ulp_ops->cnic_start(cp->ulp_handle[if_type]);

		clear_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[if_type]);
	}
}