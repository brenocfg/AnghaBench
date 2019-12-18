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
struct ps_prochandle {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pr_vaddr; } ;
typedef  TYPE_1__ prmap_t ;
typedef  int /*<<< orphan*/  m ;
struct TYPE_7__ {char const* dtpd_mod; } ;
typedef  TYPE_2__ dtrace_probedesc_t ;
typedef  int /*<<< orphan*/  Lmid_t ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  PR_LMID_EVERY ; 
 int /*<<< orphan*/  Plmid (struct ps_prochandle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* Plmid_to_map (struct ps_prochandle*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  Pobjname (struct ps_prochandle*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dt_pid_objname (char*,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  strtoul (char const*,char**,int) ; 

__attribute__((used)) static const prmap_t *
dt_pid_fix_mod(dtrace_probedesc_t *pdp, struct ps_prochandle *P)
{
	char m[MAXPATHLEN];
	Lmid_t lmid = PR_LMID_EVERY;
	const char *obj;
	const prmap_t *pmp;

	/*
	 * Pick apart the link map from the library name.
	 */
	if (strchr(pdp->dtpd_mod, '`') != NULL) {
		char *end;

		if (strncmp(pdp->dtpd_mod, "LM", 2) != 0 ||
		    !isdigit(pdp->dtpd_mod[2]))
			return (NULL);

		lmid = strtoul(&pdp->dtpd_mod[2], &end, 16);

		obj = end + 1;

		if (*end != '`' || strchr(obj, '`') != NULL)
			return (NULL);

	} else {
		obj = pdp->dtpd_mod;
	}

	if ((pmp = Plmid_to_map(P, lmid, obj)) == NULL)
		return (NULL);

	(void) Pobjname(P, pmp->pr_vaddr, m, sizeof (m));
	if ((obj = strrchr(m, '/')) == NULL)
		obj = &m[0];
	else
		obj++;

#ifdef illumos
	(void) Plmid(P, pmp->pr_vaddr, &lmid);
#endif

	dt_pid_objname(pdp->dtpd_mod, sizeof (pdp->dtpd_mod), lmid, obj);

	return (pmp);
}