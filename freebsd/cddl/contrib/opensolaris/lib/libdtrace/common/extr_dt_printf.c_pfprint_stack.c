#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int dtrd_action; int dtrd_arg; int dtrd_size; } ;
typedef  TYPE_1__ dtrace_recdesc_t ;
typedef  int dtrace_optval_t ;
struct TYPE_9__ {int* dt_options; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_10__ {int pfd_dynwidth; int pfd_flags; int pfd_width; TYPE_1__* pfd_rec; } ;
typedef  TYPE_3__ dt_pfargd_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  DTRACEACT_JSTACK 130 
#define  DTRACEACT_STACK 129 
#define  DTRACEACT_USTACK 128 
 size_t DTRACEOPT_STACKINDENT ; 
 int DT_PFCONV_DYNWIDTH ; 
 int DT_PFCONV_LEFT ; 
 int /*<<< orphan*/  assert (int) ; 
 int dt_print_stack (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int) ; 
 int dt_print_ustack (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pfprint_stack(dtrace_hdl_t *dtp, FILE *fp, const char *format,
    const dt_pfargd_t *pfd, const void *vaddr, size_t size, uint64_t normal)
{
	int width;
	dtrace_optval_t saved = dtp->dt_options[DTRACEOPT_STACKINDENT];
	const dtrace_recdesc_t *rec = pfd->pfd_rec;
	caddr_t addr = (caddr_t)vaddr;
	int err = 0;

	/*
	 * We have stashed the value of the STACKINDENT option, and we will
	 * now override it for the purposes of formatting the stack.  If the
	 * field has been specified as left-aligned (i.e. (%-#), we set the
	 * indentation to be the width.  This is a slightly odd semantic, but
	 * it's useful functionality -- and it's slightly odd to begin with to
	 * be using a single format specifier to be formatting multiple lines
	 * of text...
	 */
	if (pfd->pfd_dynwidth < 0) {
		assert(pfd->pfd_flags & DT_PFCONV_DYNWIDTH);
		width = -pfd->pfd_dynwidth;
	} else if (pfd->pfd_flags & DT_PFCONV_LEFT) {
		width = pfd->pfd_dynwidth ? pfd->pfd_dynwidth : pfd->pfd_width;
	} else {
		width = 0;
	}

	dtp->dt_options[DTRACEOPT_STACKINDENT] = width;

	switch (rec->dtrd_action) {
	case DTRACEACT_USTACK:
	case DTRACEACT_JSTACK:
		err = dt_print_ustack(dtp, fp, format, addr, rec->dtrd_arg);
		break;

	case DTRACEACT_STACK:
		err = dt_print_stack(dtp, fp, format, addr, rec->dtrd_arg,
		    rec->dtrd_size / rec->dtrd_arg);
		break;

	default:
		assert(0);
	}

	dtp->dt_options[DTRACEOPT_STACKINDENT] = saved;

	return (err);
}