#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int dtp_argc; TYPE_1__* dtp_argv; } ;
typedef  TYPE_2__ dtrace_probeinfo_t ;
struct TYPE_12__ {char* dtpd_provider; char* dtpd_mod; char* dtpd_func; char* dtpd_name; int dtpd_id; } ;
typedef  TYPE_3__ dtrace_probedesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_13__ {int dtargd_id; int dtargd_ndx; char* dtargd_native; char* dtargd_xlate; } ;
typedef  TYPE_4__ dtrace_argdesc_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_10__ {scalar_t__ dtt_type; int /*<<< orphan*/  dtt_ctfp; } ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ CTF_ERR ; 
 int /*<<< orphan*/  DTRACEIOC_PROBEARG ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 char* ctf_type_name (int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 scalar_t__ dtrace_probe_info (int /*<<< orphan*/ *,TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int g_count ; 
 scalar_t__ g_errexit ; 
 int /*<<< orphan*/  g_errs ; 
 int /*<<< orphan*/  g_fd ; 
 scalar_t__ g_verbose ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
probe(dtrace_hdl_t *dtp, const dtrace_probedesc_t *pdp, void *data)
{
	dtrace_probeinfo_t p;
	dtrace_argdesc_t arg;
	char buf[BUFSIZ];
	int i;

	(void) printf("\r%6d", ++g_count);
	(void) fflush(stdout);

	if (dtrace_probe_info(dtp, pdp, &p) != 0) {
		(void) printf(" failed to get probe info for "
		    "%s:%s:%s:%s [%d]\n", pdp->dtpd_provider, pdp->dtpd_mod,
		    pdp->dtpd_func, pdp->dtpd_name, pdp->dtpd_id);
		g_errs++;
		return (0);
	}

	for (i = 0; i < p.dtp_argc; i++) {
		if (p.dtp_argv[i].dtt_type == CTF_ERR) {
			bzero(&arg, sizeof (dtrace_argdesc_t));
			arg.dtargd_id = pdp->dtpd_id;
			arg.dtargd_ndx = i;
			(void) ioctl(g_fd, DTRACEIOC_PROBEARG, &arg);

			(void) printf(" failed to get types for args[%d] "
			    "of %s:%s:%s:%s [%d]: <%s> -> <%s>\n", i,
			    pdp->dtpd_provider, pdp->dtpd_mod, pdp->dtpd_func,
			    pdp->dtpd_name, pdp->dtpd_id,
			    arg.dtargd_native, arg.dtargd_xlate);

			g_errs++;

			if (g_errexit)
				return (-1);

		} else if (g_verbose) {
			(void) printf("%d args[%d] : %s\n", pdp->dtpd_id, i,
			    ctf_type_name(p.dtp_argv[i].dtt_ctfp,
			    p.dtp_argv[i].dtt_type, buf, sizeof (buf)));
		}
	}

	return (0);
}