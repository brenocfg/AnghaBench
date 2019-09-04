#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  k_modifier; } ;
struct TYPE_5__ {int /*<<< orphan*/  pbctx; TYPE_1__ rc; } ;
typedef  TYPE_2__ AlacEncodeContext ;

/* Variables and functions */
 int ALAC_ESCAPE_CODE ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void encode_scalar(AlacEncodeContext *s, int x,
                          int k, int write_sample_size)
{
    int divisor, q, r;

    k = FFMIN(k, s->rc.k_modifier);
    divisor = (1<<k) - 1;
    q = x / divisor;
    r = x % divisor;

    if (q > 8) {
        // write escape code and sample value directly
        put_bits(&s->pbctx, 9, ALAC_ESCAPE_CODE);
        put_bits(&s->pbctx, write_sample_size, x);
    } else {
        if (q)
            put_bits(&s->pbctx, q, (1<<q) - 1);
        put_bits(&s->pbctx, 1, 0);

        if (k != 1) {
            if (r > 0)
                put_bits(&s->pbctx, k, r+1);
            else
                put_bits(&s->pbctx, k-1, 0);
        }
    }
}