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
 int ACTION_ABORT ; 
 int ACTION_INT_WDT ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  portDISABLE_INTERRUPTS () ; 
 int /*<<< orphan*/  xt_set_intset (int) ; 

__attribute__((used)) static void __attribute__((__noinline__)) recursive_func(int recur_depth, int action)
{
    if (recur_depth > 1) {
        recursive_func(recur_depth - 1, action);
    } else if (action >= 0) {
        xt_set_intset(1 << action);
    } else if (action == ACTION_ABORT) {
        abort();
        // Todo: abort() causes problems in GDB Stub backtrace due to being 'non returning'.
    } else if (action == ACTION_INT_WDT) {
        portDISABLE_INTERRUPTS();
        while (1) {
            ;
        }
    }
}