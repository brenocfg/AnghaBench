#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int /*<<< orphan*/  n2 ;
typedef  int /*<<< orphan*/  n1 ;
struct TYPE_14__ {int /*<<< orphan*/  dtvd_name; } ;
struct TYPE_16__ {TYPE_2__ pv_desc; } ;
typedef  TYPE_4__ dt_provider_t ;
struct TYPE_17__ {TYPE_3__* pr_ident; } ;
typedef  TYPE_5__ dt_probe_t ;
struct TYPE_18__ {int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; struct TYPE_18__* dn_list; TYPE_1__* dn_ident; } ;
typedef  TYPE_6__ dt_node_t ;
struct TYPE_15__ {int /*<<< orphan*/  di_name; } ;
struct TYPE_13__ {TYPE_5__* di_data; } ;

/* Variables and functions */
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  D_PROV_INCOMPAT ; 
 scalar_t__ ctf_type_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnerror (TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char*,int,...) ; 
 int /*<<< orphan*/  dt_node_type_name (TYPE_6__*,char*,int) ; 

__attribute__((used)) static void
dt_node_provider_cmp_argv(dt_provider_t *pvp, dt_node_t *pnp, const char *kind,
    uint_t old_argc, dt_node_t *old_argv, uint_t new_argc, dt_node_t *new_argv)
{
	dt_probe_t *prp = pnp->dn_ident->di_data;
	uint_t i;

	char n1[DT_TYPE_NAMELEN];
	char n2[DT_TYPE_NAMELEN];

	if (old_argc != new_argc) {
		dnerror(pnp, D_PROV_INCOMPAT,
		    "probe %s:%s %s prototype mismatch:\n"
		    "\t current: %u arg%s\n\tprevious: %u arg%s\n",
		    pvp->pv_desc.dtvd_name, prp->pr_ident->di_name, kind,
		    new_argc, new_argc != 1 ? "s" : "",
		    old_argc, old_argc != 1 ? "s" : "");
	}

	for (i = 0; i < old_argc; i++,
	    old_argv = old_argv->dn_list, new_argv = new_argv->dn_list) {
		if (ctf_type_cmp(old_argv->dn_ctfp, old_argv->dn_type,
		    new_argv->dn_ctfp, new_argv->dn_type) == 0)
			continue;

		dnerror(pnp, D_PROV_INCOMPAT,
		    "probe %s:%s %s prototype argument #%u mismatch:\n"
		    "\t current: %s\n\tprevious: %s\n",
		    pvp->pv_desc.dtvd_name, prp->pr_ident->di_name, kind, i + 1,
		    dt_node_type_name(new_argv, n1, sizeof (n1)),
		    dt_node_type_name(old_argv, n2, sizeof (n2)));
	}
}