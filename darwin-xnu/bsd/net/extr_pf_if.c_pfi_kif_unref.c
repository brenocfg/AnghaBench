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
struct pfi_kif {scalar_t__ pfik_states; scalar_t__ pfik_rules; int /*<<< orphan*/ * pfik_ifp; } ;
typedef  enum pfi_kif_refs { ____Placeholder_pfi_kif_refs } pfi_kif_refs ;

/* Variables and functions */
#define  PFI_KIF_REF_NONE 130 
#define  PFI_KIF_REF_RULE 129 
#define  PFI_KIF_REF_STATE 128 
 int /*<<< orphan*/  PFI_MTYPE ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfi_kif*) ; 
 int /*<<< orphan*/  _FREE (struct pfi_kif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct pfi_kif* pfi_all ; 
 int /*<<< orphan*/  pfi_ifhead ; 
 int /*<<< orphan*/  pfi_ifs ; 
 int /*<<< orphan*/  printf (char*) ; 

void
pfi_kif_unref(struct pfi_kif *kif, enum pfi_kif_refs what)
{
	if (kif == NULL)
		return;

	switch (what) {
	case PFI_KIF_REF_NONE:
		break;
	case PFI_KIF_REF_RULE:
		if (kif->pfik_rules <= 0) {
			printf("pfi_kif_unref: rules refcount <= 0\n");
			return;
		}
		kif->pfik_rules--;
		break;
	case PFI_KIF_REF_STATE:
		if (kif->pfik_states <= 0) {
			printf("pfi_kif_unref: state refcount <= 0\n");
			return;
		}
		kif->pfik_states--;
		break;
	default:
		panic("pfi_kif_unref with unknown type");
	}

	if (kif->pfik_ifp != NULL || kif == pfi_all)
		return;

	if (kif->pfik_rules || kif->pfik_states)
		return;

	RB_REMOVE(pfi_ifhead, &pfi_ifs, kif);
	_FREE(kif, PFI_MTYPE);
}