#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int m; int inv; int* revtab; } ;
typedef  TYPE_1__ AVTXContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int* av_malloc (int const) ; 
 int const split_radix_permutation (int,int const,int const) ; 

int ff_tx_gen_ptwo_revtab(AVTXContext *s)
{
    const int m = s->m, inv = s->inv;

    if (!(s->revtab = av_malloc(m*sizeof(*s->revtab))))
        return AVERROR(ENOMEM);

    /* Default */
    for (int i = 0; i < m; i++) {
        int k = -split_radix_permutation(i, m, inv) & (m - 1);
        s->revtab[k] = i;
    }

    return 0;
}