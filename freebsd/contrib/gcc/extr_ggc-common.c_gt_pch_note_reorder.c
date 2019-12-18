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
struct ptr_data {void* note_ptr_cookie; int /*<<< orphan*/  reorder_fn; } ;
typedef  int /*<<< orphan*/  gt_handle_reorder ;

/* Variables and functions */
 int /*<<< orphan*/  POINTER_HASH (void*) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 struct ptr_data* htab_find_with_hash (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saving_htab ; 

void
gt_pch_note_reorder (void *obj, void *note_ptr_cookie,
		     gt_handle_reorder reorder_fn)
{
  struct ptr_data *data;

  if (obj == NULL || obj == (void *) 1)
    return;

  data = htab_find_with_hash (saving_htab, obj, POINTER_HASH (obj));
  gcc_assert (data && data->note_ptr_cookie == note_ptr_cookie);

  data->reorder_fn = reorder_fn;
}