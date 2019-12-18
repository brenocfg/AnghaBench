#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  subobj ;
struct TYPE_7__ {scalar_t__ bpo_object; int /*<<< orphan*/  bpo_os; TYPE_1__* bpo_phys; scalar_t__ bpo_havesubobj; } ;
typedef  TYPE_2__ bpobj_t ;
struct TYPE_6__ {scalar_t__ bpo_subobjs; int bpo_num_subobjs; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpobj_close (TYPE_2__*) ; 
 int bpobj_open (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmu_read (int /*<<< orphan*/ ,scalar_t__,int,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mos_obj_refd (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bpobj_count_refd(bpobj_t *bpo)
{
	mos_obj_refd(bpo->bpo_object);

	if (bpo->bpo_havesubobj && bpo->bpo_phys->bpo_subobjs != 0) {
		mos_obj_refd(bpo->bpo_phys->bpo_subobjs);
		for (uint64_t i = 0; i < bpo->bpo_phys->bpo_num_subobjs; i++) {
			uint64_t subobj;
			bpobj_t subbpo;
			int error;
			VERIFY0(dmu_read(bpo->bpo_os,
			    bpo->bpo_phys->bpo_subobjs,
			    i * sizeof (subobj), sizeof (subobj), &subobj, 0));
			error = bpobj_open(&subbpo, bpo->bpo_os, subobj);
			if (error != 0) {
				(void) printf("ERROR %u while trying to open "
				    "subobj id %llu\n",
				    error, (u_longlong_t)subobj);
				continue;
			}
			bpobj_count_refd(&subbpo);
			bpobj_close(&subbpo);
		}
	}
}