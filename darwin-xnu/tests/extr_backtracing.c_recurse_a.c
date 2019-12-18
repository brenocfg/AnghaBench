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

/* Variables and functions */
 int /*<<< orphan*/  expect_stack () ; 
 int /*<<< orphan*/  getpid () ; 
 int recurse_b (unsigned int) ; 

__attribute__((used)) static int __attribute__((noinline,not_tail_called))
recurse_a(unsigned int frames)
{
    if (frames == 1) {
        expect_stack();
        getpid();
        return 0;
    }

    return recurse_b(frames - 1) + 1;
}