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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_3__ {int /*<<< orphan*/ * kpc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kpc_counterbuf_free (int /*<<< orphan*/ *) ; 

void
kpc_thread_destroy(thread_t thread)
{
	uint64_t *buf = NULL;

	/* usual case: no kpc buf, just return */
	if( !thread->kpc_buf )
		return;

	/* otherwise, don't leak */
	buf = thread->kpc_buf;
	thread->kpc_buf = NULL;
	kpc_counterbuf_free(buf);
}