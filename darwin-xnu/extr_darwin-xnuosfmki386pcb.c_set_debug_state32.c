#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_debug_state32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* pcb_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ids; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_1__* THREAD_TO_PCB (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copy_debug_state32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ debug_state_is_valid32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ids_zone ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static kern_return_t
set_debug_state32(thread_t thread, x86_debug_state32_t *ds)
{
	x86_debug_state32_t *new_ids;
	pcb_t pcb;

	pcb = THREAD_TO_PCB(thread);

	if (debug_state_is_valid32(ds) != TRUE) {
		return KERN_INVALID_ARGUMENT;
	}

	if (pcb->ids == NULL) {
		new_ids = zalloc(ids_zone);
		bzero(new_ids, sizeof *new_ids);

		simple_lock(&pcb->lock);
		/* make sure it wasn't already alloc()'d elsewhere */
		if (pcb->ids == NULL) {
			pcb->ids = new_ids;
			simple_unlock(&pcb->lock);
		} else {
			simple_unlock(&pcb->lock);
			zfree(ids_zone, new_ids);
		}
	}


	copy_debug_state32(ds, pcb->ids, FALSE);

	return (KERN_SUCCESS);
}