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
struct traversal_state {int /*<<< orphan*/  ptrs_i; struct ptr_data** ptrs; int /*<<< orphan*/  d; } ;
struct ptr_data {scalar_t__ note_ptr_fn; int /*<<< orphan*/  type; int /*<<< orphan*/  size; int /*<<< orphan*/  obj; int /*<<< orphan*/  new_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ggc_pch_alloc_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gt_pch_p_S ; 

__attribute__((used)) static int
call_alloc (void **slot, void *state_p)
{
  struct ptr_data *d = (struct ptr_data *)*slot;
  struct traversal_state *state = (struct traversal_state *)state_p;

  d->new_addr = ggc_pch_alloc_object (state->d, d->obj, d->size,
				      d->note_ptr_fn == gt_pch_p_S,
				      d->type);
  state->ptrs[state->ptrs_i++] = d;
  return 1;
}