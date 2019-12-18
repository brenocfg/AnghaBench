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
struct mci {int /*<<< orphan*/  cp; } ;
struct crw {scalar_t__ rsc; scalar_t__ slct; } ;
struct TYPE_2__ {int /*<<< orphan*/  mcck_interruption_code; } ;

/* Variables and functions */
 scalar_t__ CRW_RSC_CPATH ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chpid_reset_count ; 
 scalar_t__ stcrw (struct crw*) ; 

__attribute__((used)) static void s390_reset_chpids_mcck_handler(void)
{
	struct crw crw;
	struct mci *mci;

	/* Check for pending channel report word. */
	mci = (struct mci *)&S390_lowcore.mcck_interruption_code;
	if (!mci->cp)
		return;
	/* Process channel report words. */
	while (stcrw(&crw) == 0) {
		/* Check for responses to RCHP. */
		if (crw.slct && crw.rsc == CRW_RSC_CPATH)
			atomic_dec(&chpid_reset_count);
	}
}