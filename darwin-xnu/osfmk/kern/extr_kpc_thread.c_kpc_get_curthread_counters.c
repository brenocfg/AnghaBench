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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  kpc_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* current_thread () ; 
 int kpc_thread_classes_count ; 
 int /*<<< orphan*/  kpc_update_thread_counters (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 

int
kpc_get_curthread_counters(uint32_t *inoutcount, uint64_t *buf)
{
	thread_t thread = current_thread();
	boolean_t enabled;

	/* buffer too small :( */
	if( *inoutcount < kpc_thread_classes_count )
		return EINVAL;

	/* copy data and actual size */
	if( !thread->kpc_buf )
		return EINVAL;

	enabled = ml_set_interrupts_enabled(FALSE);

	/* snap latest version of counters for this thread */
	kpc_update_thread_counters( current_thread() );
	
	/* copy out */
	memcpy( buf, thread->kpc_buf, 
	        kpc_thread_classes_count * sizeof(*buf) );
	*inoutcount = kpc_thread_classes_count;

	ml_set_interrupts_enabled(enabled);

	return 0;
}