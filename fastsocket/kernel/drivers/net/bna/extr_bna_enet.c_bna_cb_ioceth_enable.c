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
struct bna_ioceth {int dummy; } ;
typedef  enum bfa_status { ____Placeholder_bfa_status } bfa_status ;

/* Variables and functions */
 int /*<<< orphan*/  IOCETH_E_IOC_FAILED ; 
 int /*<<< orphan*/  IOCETH_E_IOC_READY ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_ioceth*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_cb_ioceth_enable(void *arg, enum bfa_status error)
{
	struct bna_ioceth *ioceth = (struct bna_ioceth *)arg;

	if (error)
		bfa_fsm_send_event(ioceth, IOCETH_E_IOC_FAILED);
	else
		bfa_fsm_send_event(ioceth, IOCETH_E_IOC_READY);
}