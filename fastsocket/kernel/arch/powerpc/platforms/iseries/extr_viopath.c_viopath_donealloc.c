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
struct alloc_parms {int number; int /*<<< orphan*/  done; int /*<<< orphan*/  wait_atomic; scalar_t__ used_wait_atomic; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void viopath_donealloc(void *parm, int number)
{
	struct alloc_parms *parmsp = parm;

	parmsp->number = number;
	if (parmsp->used_wait_atomic)
		atomic_set(&parmsp->wait_atomic, 0);
	else
		complete(&parmsp->done);
}