#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ iif_newidx; TYPE_4__* iif_template; scalar_t__ iif_refmerge; int /*<<< orphan*/  iif_ta; } ;
typedef  TYPE_5__ iifind_data_t ;
struct TYPE_12__ {scalar_t__ ii_type; int ii_nargs; TYPE_3__** ii_args; int /*<<< orphan*/  ii_owner; TYPE_1__* ii_dtype; int /*<<< orphan*/  ii_name; } ;
typedef  TYPE_6__ iidesc_t ;
struct TYPE_10__ {scalar_t__ ii_type; char* ii_name; char* ii_owner; int ii_nargs; TYPE_2__** ii_args; } ;
struct TYPE_9__ {scalar_t__ t_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  t_id; } ;
struct TYPE_7__ {scalar_t__ t_id; } ;

/* Variables and functions */
#define  II_GFUN 135 
#define  II_GVAR 134 
#define  II_NOT 133 
#define  II_PSYM 132 
#define  II_SFUN 131 
#define  II_SOU 130 
#define  II_SVAR 129 
#define  II_TYPE 128 
 int /*<<< orphan*/  debug (int,char*,int,char*,char*) ; 
 scalar_t__ get_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
iidesc_match(void *data, void *arg)
{
	iidesc_t *node = data;
	iifind_data_t *iif = arg;
	int i;

	if (node->ii_type != iif->iif_template->ii_type ||
	    !streq(node->ii_name, iif->iif_template->ii_name) ||
	    node->ii_dtype->t_id != iif->iif_newidx)
		return (0);

	if ((node->ii_type == II_SVAR || node->ii_type == II_SFUN) &&
	    !streq(node->ii_owner, iif->iif_template->ii_owner))
		return (0);

	if (node->ii_nargs != iif->iif_template->ii_nargs)
		return (0);

	for (i = 0; i < node->ii_nargs; i++) {
		if (get_mapping(iif->iif_ta,
		    iif->iif_template->ii_args[i]->t_id) !=
		    node->ii_args[i]->t_id)
			return (0);
	}

	if (iif->iif_refmerge) {
		switch (iif->iif_template->ii_type) {
		case II_GFUN:
		case II_SFUN:
		case II_GVAR:
		case II_SVAR:
			debug(3, "suppressing duping of %d %s from %s\n",
			    iif->iif_template->ii_type,
			    iif->iif_template->ii_name,
			    (iif->iif_template->ii_owner ?
			    iif->iif_template->ii_owner : "NULL"));
			return (0);
		case II_NOT:
		case II_PSYM:
		case II_SOU:
		case II_TYPE:
			break;
		}
	}

	return (-1);
}