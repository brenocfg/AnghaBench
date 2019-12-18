#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct function {TYPE_1__* eh; } ;
struct eh_region {int region_number; struct eh_region* outer; } ;
typedef  int /*<<< orphan*/  sbitmap ;
struct TYPE_2__ {scalar_t__ last_region_number; int region_tree; int /*<<< orphan*/  region_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TEST_BIT (int /*<<< orphan*/ ,int) ; 
 struct eh_region* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eh_region ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  sbitmap_alloc (scalar_t__) ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_zero (int /*<<< orphan*/ ) ; 

int
eh_region_outermost (struct function *ifun, int region_a, int region_b)
{
  struct eh_region *rp_a, *rp_b;
  sbitmap b_outer;

  gcc_assert (ifun->eh->last_region_number > 0);
  gcc_assert (ifun->eh->region_tree);

  rp_a = VEC_index (eh_region, ifun->eh->region_array, region_a);
  rp_b = VEC_index (eh_region, ifun->eh->region_array, region_b);
  gcc_assert (rp_a != NULL);
  gcc_assert (rp_b != NULL);

  b_outer = sbitmap_alloc (ifun->eh->last_region_number + 1);
  sbitmap_zero (b_outer);

  do
    {
      SET_BIT (b_outer, rp_b->region_number);
      rp_b = rp_b->outer;
    }
  while (rp_b);

  do
    {
      if (TEST_BIT (b_outer, rp_a->region_number))
	{
	  sbitmap_free (b_outer);
	  return rp_a->region_number;
	}
      rp_a = rp_a->outer;
    }
  while (rp_a);

  sbitmap_free (b_outer);
  return -1;
}