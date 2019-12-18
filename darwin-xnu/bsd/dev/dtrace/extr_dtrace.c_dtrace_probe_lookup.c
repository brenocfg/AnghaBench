#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* dtpv_name; } ;
typedef  TYPE_1__ dtrace_provider_t ;
typedef  scalar_t__ dtrace_provider_id_t ;
struct TYPE_6__ {int /*<<< orphan*/  dtpk_id; int /*<<< orphan*/ * dtpk_nmatch; void* dtpk_name; int /*<<< orphan*/ * dtpk_fmatch; void* dtpk_func; int /*<<< orphan*/ * dtpk_mmatch; void* dtpk_mod; int /*<<< orphan*/ * dtpk_pmatch; void* dtpk_prov; } ;
typedef  TYPE_2__ dtrace_probekey_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACE_IDNONE ; 
 int /*<<< orphan*/  DTRACE_PRIV_ALL ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int dtrace_match (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_match_nul ; 
 int /*<<< orphan*/  dtrace_match_string ; 
 int /*<<< orphan*/  dtrace_probe_lookup_match ; 
 int /*<<< orphan*/  dtrace_probekey_release (TYPE_2__*) ; 
 void* dtrace_strref (char const*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

dtrace_id_t
dtrace_probe_lookup(dtrace_provider_id_t prid, const char *mod,
    const char *func, const char *name)
{
	dtrace_probekey_t pkey;
	dtrace_id_t id;
	int match;

	lck_mtx_lock(&dtrace_lock);

	pkey.dtpk_prov = dtrace_strref(((dtrace_provider_t *)prid)->dtpv_name);
	pkey.dtpk_pmatch = &dtrace_match_string;
	pkey.dtpk_mod = dtrace_strref(mod);
	pkey.dtpk_mmatch = mod ? &dtrace_match_string : &dtrace_match_nul;
	pkey.dtpk_func = dtrace_strref(func);
	pkey.dtpk_fmatch = func ? &dtrace_match_string : &dtrace_match_nul;
	pkey.dtpk_name = dtrace_strref(name);
	pkey.dtpk_nmatch = name ? &dtrace_match_string : &dtrace_match_nul;
	pkey.dtpk_id = DTRACE_IDNONE;

	match = dtrace_match(&pkey, DTRACE_PRIV_ALL, 0, 0,
	    dtrace_probe_lookup_match, &id, NULL);

	dtrace_probekey_release(&pkey);

	lck_mtx_unlock(&dtrace_lock);

	ASSERT(match == 1 || match == 0);
	return (match ? id : 0);
}