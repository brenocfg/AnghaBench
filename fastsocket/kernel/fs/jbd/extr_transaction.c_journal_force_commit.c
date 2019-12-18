#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_6__ {int h_sync; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 TYPE_1__* journal_start (int /*<<< orphan*/ *,int) ; 
 int journal_stop (TYPE_1__*) ; 

int journal_force_commit(journal_t *journal)
{
	handle_t *handle;
	int ret;

	handle = journal_start(journal, 1);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
	} else {
		handle->h_sync = 1;
		ret = journal_stop(handle);
	}
	return ret;
}