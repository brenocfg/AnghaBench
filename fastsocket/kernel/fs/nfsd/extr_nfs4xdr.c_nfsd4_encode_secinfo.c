#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct svc_export {int ex_nflavors; TYPE_3__* ex_client; struct exp_flavor_info* ex_flavors; } ;
struct nfsd4_secinfo {struct svc_export* si_exp; } ;
struct nfsd4_compoundres {int dummy; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  data; } ;
struct gss_api_mech {TYPE_2__ gm_oid; } ;
struct exp_flavor_info {int pseudoflavor; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_6__ {TYPE_1__* flavour; } ;
struct TYPE_4__ {scalar_t__ flavour; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 int /*<<< orphan*/  RESERVE_SPACE (int) ; 
 int RPC_AUTH_GSS ; 
 int RPC_AUTH_NULL ; 
 scalar_t__ RPC_AUTH_UNIX ; 
 int /*<<< orphan*/  WRITE32 (int) ; 
 int /*<<< orphan*/  WRITEMEM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 
 struct gss_api_mech* gss_mech_get_by_pseudoflavor (int) ; 
 int /*<<< orphan*/  gss_mech_put (struct gss_api_mech*) ; 
 int gss_pseudoflavor_to_service (struct gss_api_mech*,int) ; 
 int svcauth_gss_flavor (TYPE_3__*) ; 

__attribute__((used)) static __be32
nfsd4_encode_secinfo(struct nfsd4_compoundres *resp, __be32 nfserr,
		     struct nfsd4_secinfo *secinfo)
{
	int i = 0;
	struct svc_export *exp = secinfo->si_exp;
	u32 nflavs;
	struct exp_flavor_info *flavs;
	struct exp_flavor_info def_flavs[2];
	__be32 *p;

	if (nfserr)
		goto out;
	if (exp->ex_nflavors) {
		flavs = exp->ex_flavors;
		nflavs = exp->ex_nflavors;
	} else { /* Handling of some defaults in absence of real secinfo: */
		flavs = def_flavs;
		if (exp->ex_client->flavour->flavour == RPC_AUTH_UNIX) {
			nflavs = 2;
			flavs[0].pseudoflavor = RPC_AUTH_UNIX;
			flavs[1].pseudoflavor = RPC_AUTH_NULL;
		} else if (exp->ex_client->flavour->flavour == RPC_AUTH_GSS) {
			nflavs = 1;
			flavs[0].pseudoflavor
					= svcauth_gss_flavor(exp->ex_client);
		} else {
			nflavs = 1;
			flavs[0].pseudoflavor
					= exp->ex_client->flavour->flavour;
		}
	}

	RESERVE_SPACE(4);
	WRITE32(nflavs);
	ADJUST_ARGS();
	for (i = 0; i < nflavs; i++) {
		u32 flav = flavs[i].pseudoflavor;
		struct gss_api_mech *gm = gss_mech_get_by_pseudoflavor(flav);

		if (gm) {
			RESERVE_SPACE(4);
			WRITE32(RPC_AUTH_GSS);
			ADJUST_ARGS();
			RESERVE_SPACE(4 + gm->gm_oid.len);
			WRITE32(gm->gm_oid.len);
			WRITEMEM(gm->gm_oid.data, gm->gm_oid.len);
			ADJUST_ARGS();
			RESERVE_SPACE(4);
			WRITE32(0); /* qop */
			ADJUST_ARGS();
			RESERVE_SPACE(4);
			WRITE32(gss_pseudoflavor_to_service(gm, flav));
			ADJUST_ARGS();
			gss_mech_put(gm);
		} else {
			RESERVE_SPACE(4);
			WRITE32(flav);
			ADJUST_ARGS();
		}
	}
out:
	if (exp)
		exp_put(exp);
	return nfserr;
}