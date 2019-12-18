#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_6__ {char* dtvd_name; } ;
struct TYPE_7__ {int pv_flags; int /*<<< orphan*/  pv_probes; TYPE_1__ pv_desc; } ;
typedef  TYPE_2__ dt_provider_t ;
struct TYPE_8__ {int dthi_empty; void* dthi_pfname; void* dthi_pmname; int /*<<< orphan*/ * dthi_out; int /*<<< orphan*/ * dthi_dtp; } ;
typedef  TYPE_3__ dt_header_info_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DT_PROVIDER_IMPL ; 
 void* alloca (scalar_t__) ; 
 int /*<<< orphan*/  dt_header_decl ; 
 int /*<<< orphan*/  dt_header_fmt_func (void*,char*) ; 
 int /*<<< orphan*/  dt_header_fmt_macro (void*,char*) ; 
 int /*<<< orphan*/  dt_header_probe ; 
 scalar_t__ dt_idhash_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
dt_header_provider(dtrace_hdl_t *dtp, dt_provider_t *pvp, FILE *out)
{
	dt_header_info_t info;
	const char *p;
	int i;

	if (pvp->pv_flags & DT_PROVIDER_IMPL)
		return (0);

	/*
	 * Count the instances of the '-' character since we'll need to double
	 * those up.
	 */
	p = pvp->pv_desc.dtvd_name;
	for (i = 0; (p = strchr(p, '-')) != NULL; i++)
		p++;

	info.dthi_dtp = dtp;
	info.dthi_out = out;
	info.dthi_empty = 0;

	info.dthi_pmname = alloca(strlen(pvp->pv_desc.dtvd_name) + 1);
	dt_header_fmt_macro(info.dthi_pmname, pvp->pv_desc.dtvd_name);

	info.dthi_pfname = alloca(strlen(pvp->pv_desc.dtvd_name) + 1 + i);
	dt_header_fmt_func(info.dthi_pfname, pvp->pv_desc.dtvd_name);

#ifdef __FreeBSD__
	if (fprintf(out, "#include <sys/sdt.h>\n\n") < 0)
		return (dt_set_errno(dtp, errno));
#endif
	if (fprintf(out, "#if _DTRACE_VERSION\n\n") < 0)
		return (dt_set_errno(dtp, errno));

	if (dt_idhash_iter(pvp->pv_probes, dt_header_probe, &info) != 0)
		return (-1); /* dt_errno is set for us */
	if (fprintf(out, "\n\n") < 0)
		return (dt_set_errno(dtp, errno));
	if (dt_idhash_iter(pvp->pv_probes, dt_header_decl, &info) != 0)
		return (-1); /* dt_errno is set for us */

	if (fprintf(out, "\n#else\n\n") < 0)
		return (dt_set_errno(dtp, errno));

	info.dthi_empty = 1;

	if (dt_idhash_iter(pvp->pv_probes, dt_header_probe, &info) != 0)
		return (-1); /* dt_errno is set for us */

	if (fprintf(out, "\n#endif\n\n") < 0)
		return (dt_set_errno(dtp, errno));

	return (0);
}