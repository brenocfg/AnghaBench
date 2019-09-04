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
typedef  int /*<<< orphan*/  sigjmp_buf ;

/* Variables and functions */
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 

int main() {
    sigjmp_buf env;
    volatile int flag = 0;
    if (sigsetjmp(env, 1) == 0) {
        // Cannot print anything here, because siglongjmp will
        // print a warning in between but only with ASSERTIONS enabled
        flag = 1;
        siglongjmp(env, 1);
    } else {
        if (flag) {
            puts("Success");
        }
    }
    return 0;
}