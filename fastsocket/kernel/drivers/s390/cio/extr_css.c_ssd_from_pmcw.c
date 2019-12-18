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
struct pmcw {int pim; int /*<<< orphan*/ * chpid; } ;
struct chsc_ssd_info {int path_mask; TYPE_1__* chpid; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  chp_id_init (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct chsc_ssd_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ssd_from_pmcw(struct chsc_ssd_info *ssd, struct pmcw *pmcw)
{
	int i;
	int mask;

	memset(ssd, 0, sizeof(struct chsc_ssd_info));
	ssd->path_mask = pmcw->pim;
	for (i = 0; i < 8; i++) {
		mask = 0x80 >> i;
		if (pmcw->pim & mask) {
			chp_id_init(&ssd->chpid[i]);
			ssd->chpid[i].id = pmcw->chpid[i];
		}
	}
}