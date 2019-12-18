#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_longlong_t ;
struct TYPE_8__ {int /*<<< orphan*/ * dt_vector; int /*<<< orphan*/  dt_macros; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_pfargd_t ;
struct TYPE_9__ {scalar_t__ di_id; } ;
typedef  TYPE_2__ dt_ident_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_DMISMATCH ; 
 char* alloca (int) ; 
 TYPE_2__* dt_idhash_lookup (int /*<<< orphan*/ ,char*) ; 
 int dt_printf (TYPE_1__*,int /*<<< orphan*/ *,char const*,char*) ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dtrace_uaddr2str (TYPE_1__*,scalar_t__,scalar_t__,char*,int) ; 

__attribute__((used)) static int
pfprint_uaddr(dtrace_hdl_t *dtp, FILE *fp, const char *format,
    const dt_pfargd_t *pfd, const void *addr, size_t size, uint64_t normal)
{
	char *s;
	int n, len = 256;
	uint64_t val, pid = 0;

	dt_ident_t *idp = dt_idhash_lookup(dtp->dt_macros, "target");

	switch (size) {
	case sizeof (uint32_t):
		val = (u_longlong_t)*((uint32_t *)addr);
		break;
	case sizeof (uint64_t):
		val = (u_longlong_t)*((uint64_t *)addr);
		break;
	case sizeof (uint64_t) * 2:
		pid = ((uint64_t *)(uintptr_t)addr)[0];
		val = ((uint64_t *)(uintptr_t)addr)[1];
		break;
	default:
		return (dt_set_errno(dtp, EDT_DMISMATCH));
	}

	if (pid == 0 && dtp->dt_vector == NULL && idp != NULL)
		pid = idp->di_id;

	do {
		n = len;
		s = alloca(n);
	} while ((len = dtrace_uaddr2str(dtp, pid, val, s, n)) > n);

	return (dt_printf(dtp, fp, format, s));
}