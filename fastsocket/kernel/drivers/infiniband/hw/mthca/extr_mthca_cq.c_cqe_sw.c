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
struct mthca_cqe {int owner; } ;

/* Variables and functions */
 int MTHCA_CQ_ENTRY_OWNER_HW ; 

__attribute__((used)) static inline struct mthca_cqe *cqe_sw(struct mthca_cqe *cqe)
{
	return MTHCA_CQ_ENTRY_OWNER_HW & cqe->owner ? NULL : cqe;
}