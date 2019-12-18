#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  ipz_eq_handle; } ;
struct ehca_shca {int /*<<< orphan*/  ib_device; TYPE_1__ neq; int /*<<< orphan*/  ipz_hca_handle; } ;
struct ehca_eqe {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ H_SUCCESS ; 
 int /*<<< orphan*/  NEQE_COMPLETION_EVENT ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ *,char*) ; 
 struct ehca_eqe* ehca_poll_eq (struct ehca_shca*,TYPE_1__*) ; 
 scalar_t__ hipz_h_reset_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_ec (struct ehca_shca*,int /*<<< orphan*/ ) ; 

void ehca_tasklet_neq(unsigned long data)
{
	struct ehca_shca *shca = (struct ehca_shca*)data;
	struct ehca_eqe *eqe;
	u64 ret;

	eqe = ehca_poll_eq(shca, &shca->neq);

	while (eqe) {
		if (!EHCA_BMASK_GET(NEQE_COMPLETION_EVENT, eqe->entry))
			parse_ec(shca, eqe->entry);

		eqe = ehca_poll_eq(shca, &shca->neq);
	}

	ret = hipz_h_reset_event(shca->ipz_hca_handle,
				 shca->neq.ipz_eq_handle, 0xFFFFFFFFFFFFFFFFL);

	if (ret != H_SUCCESS)
		ehca_err(&shca->ib_device, "Can't clear notification events.");

	return;
}