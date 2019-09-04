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
struct pfi_kif {int /*<<< orphan*/  pfik_states; int /*<<< orphan*/  pfik_rules; } ;
typedef  enum pfi_kif_refs { ____Placeholder_pfi_kif_refs } pfi_kif_refs ;

/* Variables and functions */
#define  PFI_KIF_REF_RULE 129 
#define  PFI_KIF_REF_STATE 128 
 int /*<<< orphan*/  panic (char*) ; 

void
pfi_kif_ref(struct pfi_kif *kif, enum pfi_kif_refs what)
{
	switch (what) {
	case PFI_KIF_REF_RULE:
		kif->pfik_rules++;
		break;
	case PFI_KIF_REF_STATE:
		kif->pfik_states++;
		break;
	default:
		panic("pfi_kif_ref with unknown type");
	}
}