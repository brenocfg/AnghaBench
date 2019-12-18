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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dt_provider_t ;
typedef  int /*<<< orphan*/  dt_probe_t ;
struct TYPE_9__ {scalar_t__ dn_kind; TYPE_1__* dn_ident; int /*<<< orphan*/  dn_provname; scalar_t__ dn_provred; struct TYPE_9__* dn_list; struct TYPE_9__* dn_probes; int /*<<< orphan*/ * dn_provider; } ;
typedef  TYPE_2__ dt_node_t ;
struct TYPE_8__ {char* di_name; int /*<<< orphan*/  di_data; } ;

/* Variables and functions */
 scalar_t__ DT_NODE_PROBE ; 
 int /*<<< orphan*/  D_PROV_INCOMPAT ; 
 int /*<<< orphan*/  D_PROV_PRDUP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dnerror (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  dt_cook_probe (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_node_provider_cmp (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_probe_declare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_probe_lookup (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static dt_node_t *
dt_cook_provider(dt_node_t *dnp, uint_t idflags)
{
	dt_provider_t *pvp = dnp->dn_provider;
	dt_node_t *pnp;

	/*
	 * If we're declaring a provider for the first time and it is unknown
	 * to dtrace(7D), insert the probe definitions into the provider's hash.
	 * If we're redeclaring a known provider, verify the interface matches.
	 */
	for (pnp = dnp->dn_probes; pnp != NULL; pnp = pnp->dn_list) {
		const char *probename = pnp->dn_ident->di_name;
		dt_probe_t *prp = dt_probe_lookup(pvp, probename);

		assert(pnp->dn_kind == DT_NODE_PROBE);

		if (prp != NULL && dnp->dn_provred) {
			dt_node_provider_cmp(pvp, pnp,
			    prp, pnp->dn_ident->di_data);
		} else if (prp == NULL && dnp->dn_provred) {
			dnerror(pnp, D_PROV_INCOMPAT,
			    "provider interface mismatch: %s\n"
			    "\t current: probe %s:%s defined\n"
			    "\tprevious: probe %s:%s not defined\n",
			    dnp->dn_provname, dnp->dn_provname,
			    probename, dnp->dn_provname, probename);
		} else if (prp != NULL) {
			dnerror(pnp, D_PROV_PRDUP, "probe redeclared: %s:%s\n",
			    dnp->dn_provname, probename);
		} else
			dt_probe_declare(pvp, pnp->dn_ident->di_data);

		dt_cook_probe(pnp, pvp);
	}

	return (dnp);
}