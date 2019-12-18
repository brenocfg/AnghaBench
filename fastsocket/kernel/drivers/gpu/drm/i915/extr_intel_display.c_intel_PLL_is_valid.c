#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct drm_device {int dummy; } ;
struct TYPE_21__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_20__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_19__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_18__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_17__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_16__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_15__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_14__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_22__ {TYPE_8__ dot; TYPE_7__ vco; TYPE_6__ n; TYPE_5__ m; TYPE_4__ m1; TYPE_3__ m2; TYPE_2__ p; TYPE_1__ p1; } ;
typedef  TYPE_9__ intel_limit_t ;
struct TYPE_13__ {scalar_t__ p1; scalar_t__ p; scalar_t__ m2; scalar_t__ m1; scalar_t__ m; scalar_t__ n; scalar_t__ vco; scalar_t__ dot; } ;
typedef  TYPE_10__ intel_clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTELPllInvalid (char*) ; 
 int /*<<< orphan*/  IS_PINEVIEW (struct drm_device*) ; 

__attribute__((used)) static bool intel_PLL_is_valid(struct drm_device *dev,
			       const intel_limit_t *limit,
			       const intel_clock_t *clock)
{
	if (clock->p1  < limit->p1.min  || limit->p1.max  < clock->p1)
		INTELPllInvalid("p1 out of range\n");
	if (clock->p   < limit->p.min   || limit->p.max   < clock->p)
		INTELPllInvalid("p out of range\n");
	if (clock->m2  < limit->m2.min  || limit->m2.max  < clock->m2)
		INTELPllInvalid("m2 out of range\n");
	if (clock->m1  < limit->m1.min  || limit->m1.max  < clock->m1)
		INTELPllInvalid("m1 out of range\n");
	if (clock->m1 <= clock->m2 && !IS_PINEVIEW(dev))
		INTELPllInvalid("m1 <= m2\n");
	if (clock->m   < limit->m.min   || limit->m.max   < clock->m)
		INTELPllInvalid("m out of range\n");
	if (clock->n   < limit->n.min   || limit->n.max   < clock->n)
		INTELPllInvalid("n out of range\n");
	if (clock->vco < limit->vco.min || limit->vco.max < clock->vco)
		INTELPllInvalid("vco out of range\n");
	/* XXX: We may need to be checking "Dot clock" depending on the multiplier,
	 * connector, etc., rather than just a single range.
	 */
	if (clock->dot < limit->dot.min || limit->dot.max < clock->dot)
		INTELPllInvalid("dot out of range\n");

	return true;
}