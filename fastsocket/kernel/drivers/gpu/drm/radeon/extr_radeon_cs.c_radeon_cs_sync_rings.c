#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct radeon_cs_parser {int nrelocs; TYPE_3__* relocs; int /*<<< orphan*/  ib; } ;
struct TYPE_6__ {TYPE_2__* robj; } ;
struct TYPE_4__ {int /*<<< orphan*/  sync_obj; } ;
struct TYPE_5__ {TYPE_1__ tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_ib_sync_to (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_cs_sync_rings(struct radeon_cs_parser *p)
{
	int i;

	for (i = 0; i < p->nrelocs; i++) {
		if (!p->relocs[i].robj)
			continue;

		radeon_ib_sync_to(&p->ib, p->relocs[i].robj->tbo.sync_obj);
	}
}