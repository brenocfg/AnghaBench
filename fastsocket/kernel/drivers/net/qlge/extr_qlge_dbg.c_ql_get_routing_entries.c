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
typedef  int u32 ;
struct ql_adapter {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEM_RT_IDX_MASK ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_get_routing_reg (struct ql_adapter*,int,int*) ; 
 int ql_sem_spinlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_get_routing_entries(struct ql_adapter *qdev, u32 *buf)
{
	int status;
	u32 value, i;

	status = ql_sem_spinlock(qdev, SEM_RT_IDX_MASK);
	if (status)
		return status;

	for (i = 0; i < 16; i++) {
		status = ql_get_routing_reg(qdev, i, &value);
		if (status) {
			netif_err(qdev, drv, qdev->ndev,
				  "Failed read of routing index register.\n");
			goto err;
		} else {
			*buf++ = value;
		}
	}
err:
	ql_sem_unlock(qdev, SEM_RT_IDX_MASK);
	return status;
}