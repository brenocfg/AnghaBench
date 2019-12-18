#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ value_range_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VR_UNDEFINED ; 
 scalar_t__ VR_VARYING ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  symbolic_range_p (TYPE_1__*) ; 
 int value_inside_range (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline bool
range_includes_zero_p (value_range_t *vr)
{
  tree zero;

  gcc_assert (vr->type != VR_UNDEFINED
              && vr->type != VR_VARYING
	      && !symbolic_range_p (vr));

  zero = build_int_cst (TREE_TYPE (vr->min), 0);
  return (value_inside_range (zero, vr) == 1);
}