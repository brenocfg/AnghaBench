#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ equiv; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ value_range_t ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  VR_VARYING ; 
 int /*<<< orphan*/  bitmap_clear (scalar_t__) ; 

__attribute__((used)) static inline void
set_value_range_to_varying (value_range_t *vr)
{
  vr->type = VR_VARYING;
  vr->min = vr->max = NULL_TREE;
  if (vr->equiv)
    bitmap_clear (vr->equiv);
}