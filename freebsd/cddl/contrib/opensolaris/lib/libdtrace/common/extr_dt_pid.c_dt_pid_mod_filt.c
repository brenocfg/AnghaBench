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
struct TYPE_6__ {int /*<<< orphan*/  pr_vaddr; } ;
typedef  TYPE_1__ prmap_t ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_7__ {char const* dpp_obj; int /*<<< orphan*/  dpp_mod; scalar_t__ dpp_lmid; int /*<<< orphan*/  dpp_pr; } ;
typedef  TYPE_2__ dt_pid_probe_t ;

/* Variables and functions */
 int DTRACE_MODNAMELEN ; 
 int /*<<< orphan*/  Plmid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  dt_pid_objname (char*,int,scalar_t__,char*) ; 
 int dt_pid_per_mod (TYPE_2__*,TYPE_1__ const*,char const*) ; 
 scalar_t__ gmatch (char const*,int /*<<< orphan*/ ) ; 
 char const* strrchr (char const*,char) ; 

__attribute__((used)) static int
dt_pid_mod_filt(void *arg, const prmap_t *pmp, const char *obj)
{
	char name[DTRACE_MODNAMELEN];
	dt_pid_probe_t *pp = arg;

	if (gmatch(obj, pp->dpp_mod))
		return (dt_pid_per_mod(pp, pmp, obj));

#ifdef illumos
	(void) Plmid(pp->dpp_pr, pmp->pr_vaddr, &pp->dpp_lmid);
#else
	pp->dpp_lmid = 0;
#endif

	if ((pp->dpp_obj = strrchr(obj, '/')) == NULL)
		pp->dpp_obj = obj;
	else
		pp->dpp_obj++;

	if (gmatch(pp->dpp_obj, pp->dpp_mod))
		return (dt_pid_per_mod(pp, pmp, obj));

#ifdef illumos
	(void) Plmid(pp->dpp_pr, pmp->pr_vaddr, &pp->dpp_lmid);
#endif

	dt_pid_objname(name, sizeof (name), pp->dpp_lmid, pp->dpp_obj);

	if (gmatch(name, pp->dpp_mod))
		return (dt_pid_per_mod(pp, pmp, obj));

	return (0);
}