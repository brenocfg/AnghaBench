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
typedef  scalar_t__ dispatch_semaphore_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRIGGERING_DEBUGID ; 
 int /*<<< orphan*/  dispatch_semaphore_signal (scalar_t__) ; 
 int /*<<< orphan*/  kdebug_trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int recurse_a (scalar_t__,unsigned int) ; 

__attribute__((used)) static int __attribute__((noinline,not_tail_called))
recurse_b(dispatch_semaphore_t spinning, unsigned int frames)
{
    if (frames == 0) {
        if (spinning) {
            dispatch_semaphore_signal(spinning);
            for (;;);
        } else {
            kdebug_trace(TRIGGERING_DEBUGID, 0, 0, 0, 0);
            return 0;
        }
    }

    return recurse_a(spinning, frames - 1) + 1;
}