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
struct _reent {int dummy; } ;
struct TYPE_4__ {scalar_t__ libc_reent; } ;
typedef  TYPE_1__ lwp_cntrl ;

/* Variables and functions */
 struct _reent* _REENT ; 
 int /*<<< orphan*/  _reclaim_reent (struct _reent*) ; 
 int /*<<< orphan*/  free (struct _reent*) ; 
 struct _reent libc_globl_reent ; 

int __libc_delete_hook(lwp_cntrl *curr_thr, lwp_cntrl *delete_thr)
{
	struct _reent *ptr;

	if(curr_thr==delete_thr)
		ptr = _REENT;
	else
		ptr = (struct _reent*)delete_thr->libc_reent;

	if(ptr && ptr!=&libc_globl_reent) {
		_reclaim_reent(ptr);
		free(ptr);
	}
	delete_thr->libc_reent = 0;

	if(curr_thr==delete_thr) _REENT = 0;

	return 1;
}