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
 int /*<<< orphan*/  memtest_compare (unsigned long*,size_t) ; 
 int /*<<< orphan*/  memtest_progress_end () ; 
 int /*<<< orphan*/  memtest_progress_start (char*,int) ; 

void memtest_compare_times(unsigned long *m, size_t bytes, int pass, int times) {
    int j;

    for (j = 0; j < times; j++) {
        memtest_progress_start("Compare",pass);
        memtest_compare(m,bytes);
        memtest_progress_end();
    }
}