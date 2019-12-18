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
struct afs_call {int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * request; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void afs_flat_call_destructor(struct afs_call *call)
{
	_enter("");

	kfree(call->request);
	call->request = NULL;
	kfree(call->buffer);
	call->buffer = NULL;
}