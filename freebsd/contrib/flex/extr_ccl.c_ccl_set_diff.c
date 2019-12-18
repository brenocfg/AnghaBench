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
 scalar_t__ ccl_contains (int,int) ; 
 int /*<<< orphan*/  ccladd (int,int) ; 
 int cclinit () ; 
 int csize ; 
 int /*<<< orphan*/  dump_cclp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int
ccl_set_diff (int a, int b)
{
    int  d, ch;

    /* create new class  */
    d = cclinit();

    /* In order to handle negation, we spin through all possible chars,
     * addding each char in a that is not in b.
     * (This could be O(n^2), but n is small and bounded.)
     */
	for ( ch = 0; ch < csize; ++ch )
        if (ccl_contains (a, ch) && !ccl_contains(b, ch))
            ccladd (d, ch);

    /* debug */
    if (0){
        fprintf(stderr, "ccl_set_diff (");
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, a);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, b);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, d);
        fprintf(stderr, "\n)\n");
    }
    return d;
}