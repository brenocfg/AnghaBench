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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  pc_t ;
struct TYPE_6__ {int ls_count; uintptr_t ls_lock; uintptr_t ls_caller; int /*<<< orphan*/ * ls_stack; scalar_t__ ls_event; } ;
typedef  TYPE_1__ lsrec_t ;
struct TYPE_7__ {int dtrd_size; scalar_t__ dtrd_offset; } ;
typedef  TYPE_2__ dtrace_recdesc_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ LS_HIST ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  fail (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ g_recsize ; 
 uintptr_t strdup (char const*) ; 

__attribute__((used)) static void
lsrec_fill(lsrec_t *lsrec, const dtrace_recdesc_t *rec, int nrecs, caddr_t data)
{
	bzero(lsrec, g_recsize);
	lsrec->ls_count = 1;

	if ((g_recsize > LS_HIST && nrecs < 4) || (nrecs < 3))
		fail(0, "truncated DTrace record");

	if (rec->dtrd_size != sizeof (uint64_t))
		fail(0, "bad event size in first record");

	/* LINTED - alignment */
	lsrec->ls_event = (uint32_t)*((uint64_t *)(data + rec->dtrd_offset));
	rec++;

#ifdef illumos
	if (rec->dtrd_size != sizeof (uintptr_t))
		fail(0, "bad lock address size in second record");

	/* LINTED - alignment */
	lsrec->ls_lock = *((uintptr_t *)(data + rec->dtrd_offset));
	rec++;
#else
	lsrec->ls_lock = strdup((const char *)(data + rec->dtrd_offset));
	rec++;
#endif

	if (rec->dtrd_size != sizeof (uintptr_t))
		fail(0, "bad caller size in third record");

	/* LINTED - alignment */
	lsrec->ls_caller = *((uintptr_t *)(data + rec->dtrd_offset));
	rec++;

	if (g_recsize > LS_HIST) {
		int frames, i;
		pc_t *stack;

		frames = rec->dtrd_size / sizeof (pc_t);
		/* LINTED - alignment */
		stack = (pc_t *)(data + rec->dtrd_offset);

		for (i = 1; i < frames; i++)
			lsrec->ls_stack[i - 1] = stack[i];
	}
}