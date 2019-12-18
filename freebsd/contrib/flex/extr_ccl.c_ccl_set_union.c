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
 int /*<<< orphan*/  ccladd (int,int /*<<< orphan*/ ) ; 
 int cclinit () ; 
 int* ccllen ; 
 int* cclmap ; 
 int /*<<< orphan*/ * ccltbl ; 
 int /*<<< orphan*/  dump_cclp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int
ccl_set_union (int a, int b)
{
    int  d, i;

    /* create new class  */
    d = cclinit();

    /* Add all of a */
    for (i = 0; i < ccllen[a]; ++i)
		ccladd (d, ccltbl[cclmap[a] + i]);

    /* Add all of b */
    for (i = 0; i < ccllen[b]; ++i)
		ccladd (d, ccltbl[cclmap[b] + i]);

    /* debug */
    if (0){
        fprintf(stderr, "ccl_set_union (%d + %d = %d", a, b, d);
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