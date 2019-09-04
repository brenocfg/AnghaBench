#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  aio_total_count; } ;

/* Variables and functions */
 int OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 TYPE_1__ aio_anchor ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int 		
aio_decrement_total_count()
{
	int old = OSDecrementAtomic(&aio_anchor.aio_total_count);
	if (old <= 0) {
		panic("Negative total AIO count!\n");
	}

	return old;
}