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
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 unsigned int FF_ARRAY_ELEMS (unsigned int*) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void bprint_pascal(AVBPrint *b, unsigned size)
{
    unsigned i, j;
    unsigned p[42];

    av_assert0(size < FF_ARRAY_ELEMS(p));

    p[0] = 1;
    av_bprintf(b, "%8d\n", 1);
    for (i = 1; i <= size; i++) {
        p[i] = 1;
        for (j = i - 1; j > 0; j--)
            p[j] = p[j] + p[j - 1];
        for (j = 0; j <= i; j++)
            av_bprintf(b, "%8d", p[j]);
        av_bprintf(b, "\n");
    }
}