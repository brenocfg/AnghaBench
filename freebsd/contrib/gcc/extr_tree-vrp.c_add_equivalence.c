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
struct TYPE_3__ {scalar_t__ equiv; } ;
typedef  TYPE_1__ value_range_t ;
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 unsigned int SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_ior_into (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__** vr_value ; 

__attribute__((used)) static void
add_equivalence (bitmap equiv, tree var)
{
  unsigned ver = SSA_NAME_VERSION (var);
  value_range_t *vr = vr_value[ver];

  bitmap_set_bit (equiv, ver);
  if (vr && vr->equiv)
    bitmap_ior_into (equiv, vr->equiv);
}