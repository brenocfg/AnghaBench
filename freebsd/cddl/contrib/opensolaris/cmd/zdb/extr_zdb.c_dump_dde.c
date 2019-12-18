#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_7__ {int /*<<< orphan*/  ddt_checksum; } ;
typedef  TYPE_1__ ddt_t ;
struct TYPE_8__ {scalar_t__ ddp_phys_birth; scalar_t__ ddp_refcnt; } ;
typedef  TYPE_2__ ddt_phys_t ;
typedef  int /*<<< orphan*/  ddt_key_t ;
struct TYPE_9__ {int /*<<< orphan*/  dde_key; TYPE_2__* dde_phys; } ;
typedef  TYPE_3__ ddt_entry_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  blkbuf ;

/* Variables and functions */
 int BP_SPRINTF_LEN ; 
 int DDT_PHYS_TYPES ; 
 int /*<<< orphan*/  ddt_bp_create (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  snprintf_blkptr (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dump_dde(const ddt_t *ddt, const ddt_entry_t *dde, uint64_t index)
{
	const ddt_phys_t *ddp = dde->dde_phys;
	const ddt_key_t *ddk = &dde->dde_key;
	const char *types[4] = { "ditto", "single", "double", "triple" };
	char blkbuf[BP_SPRINTF_LEN];
	blkptr_t blk;

	for (int p = 0; p < DDT_PHYS_TYPES; p++, ddp++) {
		if (ddp->ddp_phys_birth == 0)
			continue;
		ddt_bp_create(ddt->ddt_checksum, ddk, ddp, &blk);
		snprintf_blkptr(blkbuf, sizeof (blkbuf), &blk);
		(void) printf("index %llx refcnt %llu %s %s\n",
		    (u_longlong_t)index, (u_longlong_t)ddp->ddp_refcnt,
		    types[p], blkbuf);
	}
}