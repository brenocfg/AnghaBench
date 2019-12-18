#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* std; } ;
struct cipso_v4_doi {int type; TYPE_3__ map; } ;
struct TYPE_6__ {struct cipso_v4_doi* local; struct cipso_v4_doi* cipso; } ;
struct TYPE_5__ {struct cipso_v4_doi* local; struct cipso_v4_doi* cipso; } ;
struct TYPE_8__ {TYPE_2__ cat; TYPE_1__ lvl; } ;

/* Variables and functions */
#define  CIPSO_V4_MAP_TRANS 128 
 int /*<<< orphan*/  kfree (struct cipso_v4_doi*) ; 

void cipso_v4_doi_free(struct cipso_v4_doi *doi_def)
{
	if (doi_def == NULL)
		return;

	switch (doi_def->type) {
	case CIPSO_V4_MAP_TRANS:
		kfree(doi_def->map.std->lvl.cipso);
		kfree(doi_def->map.std->lvl.local);
		kfree(doi_def->map.std->cat.cipso);
		kfree(doi_def->map.std->cat.local);
		break;
	}
	kfree(doi_def);
}