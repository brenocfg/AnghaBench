#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ dtrace_actkind_t ;
struct TYPE_4__ {int dtad_refcnt; scalar_t__ dtad_arg; scalar_t__ dtad_uarg; int /*<<< orphan*/  dtad_ntuple; scalar_t__ dtad_kind; } ;
typedef  TYPE_1__ dtrace_actdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACEACT_ISPRINTFLIKE (scalar_t__) ; 
 scalar_t__ DTRACEACT_PRINTA ; 
 scalar_t__ KERNELBASE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dtrace_actdesc_t *
dtrace_actdesc_create(dtrace_actkind_t kind, uint32_t ntuple,
    uint64_t uarg, uint64_t arg)
{
	dtrace_actdesc_t *act;

	ASSERT(!DTRACEACT_ISPRINTFLIKE(kind) || (arg != 0 &&
	    arg >= KERNELBASE) || (arg == 0 && kind == DTRACEACT_PRINTA));

	act = kmem_zalloc(sizeof (dtrace_actdesc_t), KM_SLEEP);
	act->dtad_kind = kind;
	act->dtad_ntuple = ntuple;
	act->dtad_uarg = uarg;
	act->dtad_arg = arg;
	act->dtad_refcnt = 1;

	return (act);
}