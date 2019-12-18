#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next_containing_mem; scalar_t__ locs; } ;
typedef  TYPE_1__ cselib_val ;

/* Variables and functions */
 int /*<<< orphan*/  cselib_hash_table ; 
 int /*<<< orphan*/  discard_useless_locs ; 
 int /*<<< orphan*/  discard_useless_values ; 
 TYPE_1__ dummy_val ; 
 TYPE_1__* first_containing_mem ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  htab_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_useless_values ; 
 scalar_t__ values_became_useless ; 

__attribute__((used)) static void
remove_useless_values (void)
{
  cselib_val **p, *v;
  /* First pass: eliminate locations that reference the value.  That in
     turn can make more values useless.  */
  do
    {
      values_became_useless = 0;
      htab_traverse (cselib_hash_table, discard_useless_locs, 0);
    }
  while (values_became_useless);

  /* Second pass: actually remove the values.  */

  p = &first_containing_mem;
  for (v = *p; v != &dummy_val; v = v->next_containing_mem)
    if (v->locs)
      {
	*p = v;
	p = &(*p)->next_containing_mem;
      }
  *p = &dummy_val;

  htab_traverse (cselib_hash_table, discard_useless_values, 0);

  gcc_assert (!n_useless_values);
}