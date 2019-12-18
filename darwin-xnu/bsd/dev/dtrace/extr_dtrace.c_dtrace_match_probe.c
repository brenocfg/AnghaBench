#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zoneid_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_7__ {int /*<<< orphan*/  dtpv_name; scalar_t__ dtpv_defunct; } ;
typedef  TYPE_1__ dtrace_provider_t ;
struct TYPE_8__ {int (* dtpk_pmatch ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* dtpk_mmatch ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* dtpk_fmatch ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* dtpk_nmatch ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dtpk_name; int /*<<< orphan*/  dtpk_func; int /*<<< orphan*/  dtpk_mod; int /*<<< orphan*/  dtpk_prov; } ;
typedef  TYPE_2__ dtrace_probekey_t ;
struct TYPE_9__ {int /*<<< orphan*/  dtpr_name; int /*<<< orphan*/  dtpr_func; int /*<<< orphan*/  dtpr_mod; TYPE_1__* dtpr_provider; } ;
typedef  TYPE_3__ dtrace_probe_t ;

/* Variables and functions */
 scalar_t__ dtrace_match_priv (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_match_probe(const dtrace_probe_t *prp, const dtrace_probekey_t *pkp,
    uint32_t priv, uid_t uid, zoneid_t zoneid)
{
	dtrace_provider_t *pvp = prp->dtpr_provider;
	int rv;

	if (pvp->dtpv_defunct)
		return (0);

	if ((rv = pkp->dtpk_pmatch(pvp->dtpv_name, pkp->dtpk_prov, 0)) <= 0)
		return (rv);

	if ((rv = pkp->dtpk_mmatch(prp->dtpr_mod, pkp->dtpk_mod, 0)) <= 0)
		return (rv);

	if ((rv = pkp->dtpk_fmatch(prp->dtpr_func, pkp->dtpk_func, 0)) <= 0)
		return (rv);

	if ((rv = pkp->dtpk_nmatch(prp->dtpr_name, pkp->dtpk_name, 0)) <= 0)
		return (rv);

	if (dtrace_match_priv(prp, priv, uid, zoneid) == 0)
		return (0);

	return (rv);
}