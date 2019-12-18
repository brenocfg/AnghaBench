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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  RangeCoder ;

/* Variables and functions */
 int FFABS (int) ; 
 int FFMIN (int,int) ; 
 int av_log2 (int const) ; 
 int /*<<< orphan*/  put_rac (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 

void put_symbol_inline(RangeCoder *c,
                                                          uint8_t *state, int v,
                                                          int is_signed,
                                                          uint64_t rc_stat[256][2],
                                                          uint64_t rc_stat2[32][2])
{
    int i;

#define put_rac(C, S, B)                        \
    do {                                        \
        if (rc_stat) {                          \
            rc_stat[*(S)][B]++;                 \
            rc_stat2[(S) - state][B]++;         \
        }                                       \
        put_rac(C, S, B);                       \
    } while (0)

    if (v) {
        const int a = FFABS(v);
        const int e = av_log2(a);
        put_rac(c, state + 0, 0);
        if (e <= 9) {
            for (i = 0; i < e; i++)
                put_rac(c, state + 1 + i, 1);  // 1..10
            put_rac(c, state + 1 + i, 0);

            for (i = e - 1; i >= 0; i--)
                put_rac(c, state + 22 + i, (a >> i) & 1);  // 22..31

            if (is_signed)
                put_rac(c, state + 11 + e, v < 0);  // 11..21
        } else {
            for (i = 0; i < e; i++)
                put_rac(c, state + 1 + FFMIN(i, 9), 1);  // 1..10
            put_rac(c, state + 1 + 9, 0);

            for (i = e - 1; i >= 0; i--)
                put_rac(c, state + 22 + FFMIN(i, 9), (a >> i) & 1);  // 22..31

            if (is_signed)
                put_rac(c, state + 11 + 10, v < 0);  // 11..21
        }
    } else {
        put_rac(c, state + 0, 1);
    }
#undef put_rac
}