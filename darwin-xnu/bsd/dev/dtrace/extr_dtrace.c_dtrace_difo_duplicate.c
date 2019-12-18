#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
typedef  int /*<<< orphan*/  dtrace_difv_t ;
struct TYPE_6__ {scalar_t__ dtdo_refcnt; int dtdo_len; size_t dtdo_strlen; int dtdo_intlen; int dtdo_varlen; int /*<<< orphan*/ * dtdo_vartab; int /*<<< orphan*/ * dtdo_inttab; int /*<<< orphan*/ * dtdo_strtab; int /*<<< orphan*/ * dtdo_buf; } ;
typedef  TYPE_1__ dtrace_difo_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dtrace_difo_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dtrace_difo_t *
dtrace_difo_duplicate(dtrace_difo_t *dp, dtrace_vstate_t *vstate)
{
	dtrace_difo_t *new;
	size_t sz;

	ASSERT(dp->dtdo_buf != NULL);
	ASSERT(dp->dtdo_refcnt != 0);

	new = kmem_zalloc(sizeof (dtrace_difo_t), KM_SLEEP);

	ASSERT(dp->dtdo_buf != NULL);
	sz = dp->dtdo_len * sizeof (dif_instr_t);
	new->dtdo_buf = kmem_alloc(sz, KM_SLEEP);
	bcopy(dp->dtdo_buf, new->dtdo_buf, sz);
	new->dtdo_len = dp->dtdo_len;

	if (dp->dtdo_strtab != NULL) {
		ASSERT(dp->dtdo_strlen != 0);
		new->dtdo_strtab = kmem_alloc(dp->dtdo_strlen, KM_SLEEP);
		bcopy(dp->dtdo_strtab, new->dtdo_strtab, dp->dtdo_strlen);
		new->dtdo_strlen = dp->dtdo_strlen;
	}

	if (dp->dtdo_inttab != NULL) {
		ASSERT(dp->dtdo_intlen != 0);
		sz = dp->dtdo_intlen * sizeof (uint64_t);
		new->dtdo_inttab = kmem_alloc(sz, KM_SLEEP);
		bcopy(dp->dtdo_inttab, new->dtdo_inttab, sz);
		new->dtdo_intlen = dp->dtdo_intlen;
	}

	if (dp->dtdo_vartab != NULL) {
		ASSERT(dp->dtdo_varlen != 0);
		sz = dp->dtdo_varlen * sizeof (dtrace_difv_t);
		new->dtdo_vartab = kmem_alloc(sz, KM_SLEEP);
		bcopy(dp->dtdo_vartab, new->dtdo_vartab, sz);
		new->dtdo_varlen = dp->dtdo_varlen;
	}

	dtrace_difo_init(new, vstate);
	return (new);
}