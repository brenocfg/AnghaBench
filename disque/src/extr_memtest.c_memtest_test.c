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
 int /*<<< orphan*/  ULONG_ONEZERO ; 
 unsigned long ULONG_ZEROONE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 unsigned long* malloc (size_t) ; 
 int /*<<< orphan*/  memtest_addressing (unsigned long*,size_t) ; 
 int /*<<< orphan*/  memtest_compare_times (unsigned long*,size_t,int,int) ; 
 int /*<<< orphan*/  memtest_fill_random (unsigned long*,size_t) ; 
 int /*<<< orphan*/  memtest_fill_value (unsigned long*,size_t,int /*<<< orphan*/ ,unsigned long,char) ; 
 int /*<<< orphan*/  memtest_progress_end () ; 
 int /*<<< orphan*/  memtest_progress_start (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void memtest_test(size_t megabytes, int passes) {
    size_t bytes = megabytes*1024*1024;
    unsigned long *m = malloc(bytes);
    int pass = 0;

    if (m == NULL) {
        fprintf(stderr,"Unable to allocate %zu megabytes: %s",
            megabytes, strerror(errno));
        exit(1);
    }
    while (pass != passes) {
        pass++;

        memtest_progress_start("Addressing test",pass);
        memtest_addressing(m,bytes);
        memtest_progress_end();

        memtest_progress_start("Random fill",pass);
        memtest_fill_random(m,bytes);
        memtest_progress_end();
        memtest_compare_times(m,bytes,pass,4);

        memtest_progress_start("Solid fill",pass);
        memtest_fill_value(m,bytes,0,(unsigned long)-1,'S');
        memtest_progress_end();
        memtest_compare_times(m,bytes,pass,4);

        memtest_progress_start("Checkerboard fill",pass);
        memtest_fill_value(m,bytes,ULONG_ONEZERO,ULONG_ZEROONE,'C');
        memtest_progress_end();
        memtest_compare_times(m,bytes,pass,4);
    }
    free(m);
}