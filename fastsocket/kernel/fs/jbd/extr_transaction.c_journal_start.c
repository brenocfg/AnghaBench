#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_11__ {int /*<<< orphan*/  h_ref; TYPE_1__* h_transaction; } ;
typedef  TYPE_2__ handle_t ;
struct TYPE_12__ {TYPE_2__* journal_info; } ;
struct TYPE_10__ {int /*<<< orphan*/ * t_journal; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EROFS ; 
 TYPE_2__* ERR_PTR (int) ; 
 int /*<<< orphan*/  J_ASSERT (int) ; 
 TYPE_8__* current ; 
 int /*<<< orphan*/  jbd_free_handle (TYPE_2__*) ; 
 TYPE_2__* journal_current_handle () ; 
 TYPE_2__* new_handle (int) ; 
 int start_this_handle (int /*<<< orphan*/ *,TYPE_2__*) ; 

handle_t *journal_start(journal_t *journal, int nblocks)
{
	handle_t *handle = journal_current_handle();
	int err;

	if (!journal)
		return ERR_PTR(-EROFS);

	if (handle) {
		J_ASSERT(handle->h_transaction->t_journal == journal);
		handle->h_ref++;
		return handle;
	}

	handle = new_handle(nblocks);
	if (!handle)
		return ERR_PTR(-ENOMEM);

	current->journal_info = handle;

	err = start_this_handle(journal, handle);
	if (err < 0) {
		jbd_free_handle(handle);
		current->journal_info = NULL;
		handle = ERR_PTR(err);
		goto out;
	}
out:
	return handle;
}