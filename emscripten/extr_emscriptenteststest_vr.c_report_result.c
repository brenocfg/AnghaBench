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
 int /*<<< orphan*/  emscripten_cancel_main_loop () ; 
 int /*<<< orphan*/  printf (char*) ; 

void report_result(int result) {
    emscripten_cancel_main_loop();
    if (result == 0) {
        printf("Test successful!\n");
    } else {
        printf("Test failed!\n");
    }
#ifdef REPORT_RESULT
    REPORT_RESULT(result);
#endif
}