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

/* Variables and functions */
 int /*<<< orphan*/  VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ reserv_sets_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserv_sets_t ; 
 int /*<<< orphan*/  state_reservs ; 

__attribute__((used)) static void
remove_state_duplicate_reservs (void)
{
  size_t i, j;

  for (i = 1, j = 0; i < VEC_length (reserv_sets_t, state_reservs); i++)
    if (reserv_sets_cmp (VEC_index (reserv_sets_t, state_reservs, j),
			 VEC_index (reserv_sets_t, state_reservs, i)))
      {
	j++;
	VEC_replace (reserv_sets_t, state_reservs, j,
		     VEC_index (reserv_sets_t, state_reservs, i));
      }
  VEC_truncate (reserv_sets_t, state_reservs, j + 1);
}