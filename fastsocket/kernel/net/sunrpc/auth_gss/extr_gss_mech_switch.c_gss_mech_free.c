#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pf_desc {int /*<<< orphan*/ * auth_domain_name; } ;
struct gss_api_mech {int gm_pf_num; struct pf_desc* gm_pfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gss_mech_free(struct gss_api_mech *gm)
{
	struct pf_desc *pf;
	int i;

	for (i = 0; i < gm->gm_pf_num; i++) {
		pf = &gm->gm_pfs[i];
		kfree(pf->auth_domain_name);
		pf->auth_domain_name = NULL;
	}
}