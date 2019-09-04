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
struct TYPE_4__ {int f_code; int sprite_warping_accuracy; int workaround_bugs; int quarter_sample; int real_sprite_warping_points; int** sprite_offset; int** sprite_delta; int mb_x; int mb_y; } ;
struct TYPE_5__ {int divx_version; int divx_build; int* sprite_shift; TYPE_1__ m; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg4DecContext ;

/* Variables and functions */
 int FF_BUG_AMV ; 
 int RSHIFT (int,int const) ; 

__attribute__((used)) static inline int get_amv(Mpeg4DecContext *ctx, int n)
{
    MpegEncContext *s = &ctx->m;
    int x, y, mb_v, sum, dx, dy, shift;
    int len     = 1 << (s->f_code + 4);
    const int a = s->sprite_warping_accuracy;

    if (s->workaround_bugs & FF_BUG_AMV)
        len >>= s->quarter_sample;

    if (s->real_sprite_warping_points == 1) {
        if (ctx->divx_version == 500 && ctx->divx_build == 413 && a >= s->quarter_sample)
            sum = s->sprite_offset[0][n] / (1 << (a - s->quarter_sample));
        else
            sum = RSHIFT(s->sprite_offset[0][n] * (1 << s->quarter_sample), a);
    } else {
        dx    = s->sprite_delta[n][0];
        dy    = s->sprite_delta[n][1];
        shift = ctx->sprite_shift[0];
        if (n)
            dy -= 1 << (shift + a + 1);
        else
            dx -= 1 << (shift + a + 1);
        mb_v = s->sprite_offset[0][n] + dx * s->mb_x * 16 + dy * s->mb_y * 16;

        sum = 0;
        for (y = 0; y < 16; y++) {
            int v;

            v = mb_v + dy * y;
            // FIXME optimize
            for (x = 0; x < 16; x++) {
                sum += v >> shift;
                v   += dx;
            }
        }
        sum = RSHIFT(sum, a + 8 - s->quarter_sample);
    }

    if (sum < -len)
        sum = -len;
    else if (sum >= len)
        sum = len - 1;

    return sum;
}