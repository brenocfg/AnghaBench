#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ii_type; int /*<<< orphan*/  ii_owner; int /*<<< orphan*/  ii_name; } ;
typedef  TYPE_1__ iidesc_t ;
struct TYPE_4__ {TYPE_1__* iim_ret; int /*<<< orphan*/ * iim_file; int /*<<< orphan*/  iim_bind; int /*<<< orphan*/  iim_fuzzy; int /*<<< orphan*/ * iim_name; } ;
typedef  TYPE_2__ iidesc_match_t ;

/* Variables and functions */
#define  II_GFUN 131 
#define  II_GVAR 130 
#define  II_SFUN 129 
#define  II_SVAR 128 
 int /*<<< orphan*/  STB_GLOBAL ; 
 int /*<<< orphan*/  STB_LOCAL ; 
 scalar_t__ streq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
matching_iidesc(void *arg1, void *arg2)
{
	iidesc_t *iidesc = arg1;
	iidesc_match_t *match = arg2;
	if (streq(iidesc->ii_name, match->iim_name) == 0)
		return (0);

	switch (iidesc->ii_type) {
	case II_GFUN:
	case II_GVAR:
		if (match->iim_bind == STB_GLOBAL) {
			match->iim_ret = iidesc;
			return (-1);
		} else if (match->iim_fuzzy && match->iim_ret == NULL) {
			match->iim_ret = iidesc;
			/* continue to look for strong match */
			return (0);
		}
		break;
	case II_SFUN:
	case II_SVAR:
		if (match->iim_bind == STB_LOCAL &&
		    match->iim_file != NULL &&
		    streq(iidesc->ii_owner, match->iim_file)) {
			match->iim_ret = iidesc;
			return (-1);
		}
		break;
	default:
		break;
	}
	return (0);
}