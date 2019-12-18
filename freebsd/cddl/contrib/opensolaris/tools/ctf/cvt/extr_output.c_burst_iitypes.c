#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ii_type; int ii_flags; TYPE_1__* ii_dtype; } ;
typedef  TYPE_2__ iidesc_t ;
struct TYPE_7__ {int /*<<< orphan*/  iib_tdtd; } ;
typedef  TYPE_3__ iiburst_t ;
struct TYPE_5__ {int /*<<< orphan*/  t_flags; } ;

/* Variables and functions */
 int IIDESC_F_USED ; 
#define  II_GFUN 131 
#define  II_GVAR 130 
#define  II_SFUN 129 
#define  II_SVAR 128 
 int /*<<< orphan*/  TDESC_F_ISROOT ; 
 int /*<<< orphan*/  iitraverse_td (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
burst_iitypes(void *data, void *arg)
{
	iidesc_t *ii = data;
	iiburst_t *iiburst = arg;

	switch (ii->ii_type) {
	case II_GFUN:
	case II_SFUN:
	case II_GVAR:
	case II_SVAR:
		if (!(ii->ii_flags & IIDESC_F_USED))
			return (0);
		break;
	default:
		break;
	}

	ii->ii_dtype->t_flags |= TDESC_F_ISROOT;
	(void) iitraverse_td(ii, iiburst->iib_tdtd);
	return (1);
}