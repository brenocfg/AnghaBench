#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_7__ {int /*<<< orphan*/ * table; } ;
struct TYPE_5__ {int sprite_warping_accuracy; int width; int height; int real_sprite_warping_points; int** sprite_offset; int** sprite_delta; int /*<<< orphan*/  avctx; } ;
struct TYPE_6__ {int num_sprite_warping_points; int divx_version; int divx_build; int** sprite_traj; int* sprite_shift; TYPE_1__ m; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg4DecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ FFABS (int) ; 
 int FFMIN (int,int) ; 
 scalar_t__ INT_MAX ; 
 int ROUNDED_DIV (int,int) ; 
 int /*<<< orphan*/  SPRITE_TRAJ_VLC_BITS ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_marker (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int get_xbits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ llabs (int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ sprite_trajectory ; 

__attribute__((used)) static int mpeg4_decode_sprite_trajectory(Mpeg4DecContext *ctx, GetBitContext *gb)
{
    MpegEncContext *s = &ctx->m;
    int a     = 2 << s->sprite_warping_accuracy;
    int rho   = 3  - s->sprite_warping_accuracy;
    int r     = 16 / a;
    int alpha = 1;
    int beta  = 0;
    int w     = s->width;
    int h     = s->height;
    int min_ab, i, w2, h2, w3, h3;
    int sprite_ref[4][2];
    int virtual_ref[2][2];
    int64_t sprite_offset[2][2];
    int64_t sprite_delta[2][2];

    // only true for rectangle shapes
    const int vop_ref[4][2] = { { 0, 0 },         { s->width, 0 },
                                { 0, s->height }, { s->width, s->height } };
    int d[4][2]             = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };

    if (w <= 0 || h <= 0)
        return AVERROR_INVALIDDATA;

    /* the decoder was not properly initialized and we cannot continue */
    if (sprite_trajectory.table == NULL)
        return AVERROR_INVALIDDATA;

    for (i = 0; i < ctx->num_sprite_warping_points; i++) {
        int length;
        int x = 0, y = 0;

        length = get_vlc2(gb, sprite_trajectory.table, SPRITE_TRAJ_VLC_BITS, 3);
        if (length > 0)
            x = get_xbits(gb, length);

        if (!(ctx->divx_version == 500 && ctx->divx_build == 413))
            check_marker(s->avctx, gb, "before sprite_trajectory");

        length = get_vlc2(gb, sprite_trajectory.table, SPRITE_TRAJ_VLC_BITS, 3);
        if (length > 0)
            y = get_xbits(gb, length);

        check_marker(s->avctx, gb, "after sprite_trajectory");
        ctx->sprite_traj[i][0] = d[i][0] = x;
        ctx->sprite_traj[i][1] = d[i][1] = y;
    }
    for (; i < 4; i++)
        ctx->sprite_traj[i][0] = ctx->sprite_traj[i][1] = 0;

    while ((1 << alpha) < w)
        alpha++;
    while ((1 << beta) < h)
        beta++;  /* typo in the MPEG-4 std for the definition of w' and h' */
    w2 = 1 << alpha;
    h2 = 1 << beta;

    // Note, the 4th point isn't used for GMC
    if (ctx->divx_version == 500 && ctx->divx_build == 413) {
        sprite_ref[0][0] = a * vop_ref[0][0] + d[0][0];
        sprite_ref[0][1] = a * vop_ref[0][1] + d[0][1];
        sprite_ref[1][0] = a * vop_ref[1][0] + d[0][0] + d[1][0];
        sprite_ref[1][1] = a * vop_ref[1][1] + d[0][1] + d[1][1];
        sprite_ref[2][0] = a * vop_ref[2][0] + d[0][0] + d[2][0];
        sprite_ref[2][1] = a * vop_ref[2][1] + d[0][1] + d[2][1];
    } else {
        sprite_ref[0][0] = (a >> 1) * (2 * vop_ref[0][0] + d[0][0]);
        sprite_ref[0][1] = (a >> 1) * (2 * vop_ref[0][1] + d[0][1]);
        sprite_ref[1][0] = (a >> 1) * (2 * vop_ref[1][0] + d[0][0] + d[1][0]);
        sprite_ref[1][1] = (a >> 1) * (2 * vop_ref[1][1] + d[0][1] + d[1][1]);
        sprite_ref[2][0] = (a >> 1) * (2 * vop_ref[2][0] + d[0][0] + d[2][0]);
        sprite_ref[2][1] = (a >> 1) * (2 * vop_ref[2][1] + d[0][1] + d[2][1]);
    }
    /* sprite_ref[3][0] = (a >> 1) * (2 * vop_ref[3][0] + d[0][0] + d[1][0] + d[2][0] + d[3][0]);
     * sprite_ref[3][1] = (a >> 1) * (2 * vop_ref[3][1] + d[0][1] + d[1][1] + d[2][1] + d[3][1]); */

    /* This is mostly identical to the MPEG-4 std (and is totally unreadable
     * because of that...). Perhaps it should be reordered to be more readable.
     * The idea behind this virtual_ref mess is to be able to use shifts later
     * per pixel instead of divides so the distance between points is converted
     * from w&h based to w2&h2 based which are of the 2^x form. */
    virtual_ref[0][0] = 16 * (vop_ref[0][0] + w2) +
                         ROUNDED_DIV(((w - w2) *
                                           (r * sprite_ref[0][0] - 16LL * vop_ref[0][0]) +
                                      w2 * (r * sprite_ref[1][0] - 16LL * vop_ref[1][0])), w);
    virtual_ref[0][1] = 16 * vop_ref[0][1] +
                        ROUNDED_DIV(((w - w2) *
                                          (r * sprite_ref[0][1] - 16LL * vop_ref[0][1]) +
                                     w2 * (r * sprite_ref[1][1] - 16LL * vop_ref[1][1])), w);
    virtual_ref[1][0] = 16 * vop_ref[0][0] +
                        ROUNDED_DIV(((h - h2) * (r * sprite_ref[0][0] - 16LL * vop_ref[0][0]) +
                                           h2 * (r * sprite_ref[2][0] - 16LL * vop_ref[2][0])), h);
    virtual_ref[1][1] = 16 * (vop_ref[0][1] + h2) +
                        ROUNDED_DIV(((h - h2) * (r * sprite_ref[0][1] - 16LL * vop_ref[0][1]) +
                                           h2 * (r * sprite_ref[2][1] - 16LL * vop_ref[2][1])), h);

    switch (ctx->num_sprite_warping_points) {
    case 0:
        sprite_offset[0][0]    =
        sprite_offset[0][1]    =
        sprite_offset[1][0]    =
        sprite_offset[1][1]    = 0;
        sprite_delta[0][0]     = a;
        sprite_delta[0][1]     =
        sprite_delta[1][0]     = 0;
        sprite_delta[1][1]     = a;
        ctx->sprite_shift[0]   =
        ctx->sprite_shift[1]   = 0;
        break;
    case 1:     // GMC only
        sprite_offset[0][0]    = sprite_ref[0][0] - a * vop_ref[0][0];
        sprite_offset[0][1]    = sprite_ref[0][1] - a * vop_ref[0][1];
        sprite_offset[1][0]    = ((sprite_ref[0][0] >> 1) | (sprite_ref[0][0] & 1)) -
                                 a * (vop_ref[0][0] / 2);
        sprite_offset[1][1]    = ((sprite_ref[0][1] >> 1) | (sprite_ref[0][1] & 1)) -
                                 a * (vop_ref[0][1] / 2);
        sprite_delta[0][0]     = a;
        sprite_delta[0][1]     =
        sprite_delta[1][0]     = 0;
        sprite_delta[1][1]     = a;
        ctx->sprite_shift[0]   =
        ctx->sprite_shift[1]   = 0;
        break;
    case 2:
        sprite_offset[0][0]    = ((int64_t)      sprite_ref[0][0] * (1 << alpha + rho)) +
                                 ((int64_t) -r * sprite_ref[0][0] + virtual_ref[0][0]) *
                                 ((int64_t)        -vop_ref[0][0]) +
                                 ((int64_t)  r * sprite_ref[0][1] - virtual_ref[0][1]) *
                                 ((int64_t)        -vop_ref[0][1]) + (1 << (alpha + rho - 1));
        sprite_offset[0][1]    = ((int64_t)      sprite_ref[0][1] * (1 << alpha + rho)) +
                                 ((int64_t) -r * sprite_ref[0][1] + virtual_ref[0][1]) *
                                 ((int64_t)        -vop_ref[0][0]) +
                                 ((int64_t) -r * sprite_ref[0][0] + virtual_ref[0][0]) *
                                 ((int64_t)        -vop_ref[0][1]) + (1 << (alpha + rho - 1));
        sprite_offset[1][0]    = (((int64_t)-r * sprite_ref[0][0] + virtual_ref[0][0]) *
                                  ((int64_t)-2 *    vop_ref[0][0] + 1) +
                                  ((int64_t) r * sprite_ref[0][1] - virtual_ref[0][1]) *
                                  ((int64_t)-2 *    vop_ref[0][1] + 1) + 2 * w2 * r *
                                   (int64_t)     sprite_ref[0][0] - 16 * w2 + (1 << (alpha + rho + 1)));
        sprite_offset[1][1]    = (((int64_t)-r * sprite_ref[0][1] + virtual_ref[0][1]) *
                                  ((int64_t)-2 *    vop_ref[0][0] + 1) +
                                  ((int64_t)-r * sprite_ref[0][0] + virtual_ref[0][0]) *
                                  ((int64_t)-2 *    vop_ref[0][1] + 1) + 2 * w2 * r *
                                  (int64_t)      sprite_ref[0][1] - 16 * w2 + (1 << (alpha + rho + 1)));
        sprite_delta[0][0] = (-r * sprite_ref[0][0] + virtual_ref[0][0]);
        sprite_delta[0][1] = (+r * sprite_ref[0][1] - virtual_ref[0][1]);
        sprite_delta[1][0] = (-r * sprite_ref[0][1] + virtual_ref[0][1]);
        sprite_delta[1][1] = (-r * sprite_ref[0][0] + virtual_ref[0][0]);

        ctx->sprite_shift[0]  = alpha + rho;
        ctx->sprite_shift[1]  = alpha + rho + 2;
        break;
    case 3:
        min_ab = FFMIN(alpha, beta);
        w3     = w2 >> min_ab;
        h3     = h2 >> min_ab;
        sprite_offset[0][0]    = ((int64_t)sprite_ref[0][0] * (1 << (alpha + beta + rho - min_ab))) +
                                 ((int64_t)-r * sprite_ref[0][0] + virtual_ref[0][0]) * h3 * (-vop_ref[0][0]) +
                                 ((int64_t)-r * sprite_ref[0][0] + virtual_ref[1][0]) * w3 * (-vop_ref[0][1]) +
                                 ((int64_t)1 << (alpha + beta + rho - min_ab - 1));
        sprite_offset[0][1]    = ((int64_t)sprite_ref[0][1] * (1 << (alpha + beta + rho - min_ab))) +
                                 ((int64_t)-r * sprite_ref[0][1] + virtual_ref[0][1]) * h3 * (-vop_ref[0][0]) +
                                 ((int64_t)-r * sprite_ref[0][1] + virtual_ref[1][1]) * w3 * (-vop_ref[0][1]) +
                                 ((int64_t)1 << (alpha + beta + rho - min_ab - 1));
        sprite_offset[1][0]    = ((int64_t)-r * sprite_ref[0][0] + virtual_ref[0][0]) * h3 * (-2 * vop_ref[0][0] + 1) +
                                 ((int64_t)-r * sprite_ref[0][0] + virtual_ref[1][0]) * w3 * (-2 * vop_ref[0][1] + 1) +
                                  (int64_t)2 * w2 * h3 * r * sprite_ref[0][0] - 16 * w2 * h3 +
                                 ((int64_t)1 << (alpha + beta + rho - min_ab + 1));
        sprite_offset[1][1]    = ((int64_t)-r * sprite_ref[0][1] + virtual_ref[0][1]) * h3 * (-2 * vop_ref[0][0] + 1) +
                                 ((int64_t)-r * sprite_ref[0][1] + virtual_ref[1][1]) * w3 * (-2 * vop_ref[0][1] + 1) +
                                  (int64_t)2 * w2 * h3 * r * sprite_ref[0][1] - 16 * w2 * h3 +
                                 ((int64_t)1 << (alpha + beta + rho - min_ab + 1));
        sprite_delta[0][0] = (-r * (int64_t)sprite_ref[0][0] + virtual_ref[0][0]) * h3;
        sprite_delta[0][1] = (-r * (int64_t)sprite_ref[0][0] + virtual_ref[1][0]) * w3;
        sprite_delta[1][0] = (-r * (int64_t)sprite_ref[0][1] + virtual_ref[0][1]) * h3;
        sprite_delta[1][1] = (-r * (int64_t)sprite_ref[0][1] + virtual_ref[1][1]) * w3;

        ctx->sprite_shift[0]  = alpha + beta + rho - min_ab;
        ctx->sprite_shift[1]  = alpha + beta + rho - min_ab + 2;
        break;
    }
    /* try to simplify the situation */
    if (sprite_delta[0][0] == a << ctx->sprite_shift[0] &&
        sprite_delta[0][1] == 0 &&
        sprite_delta[1][0] == 0 &&
        sprite_delta[1][1] == a << ctx->sprite_shift[0]) {
        sprite_offset[0][0] >>= ctx->sprite_shift[0];
        sprite_offset[0][1] >>= ctx->sprite_shift[0];
        sprite_offset[1][0] >>= ctx->sprite_shift[1];
        sprite_offset[1][1] >>= ctx->sprite_shift[1];
        sprite_delta[0][0] = a;
        sprite_delta[0][1] = 0;
        sprite_delta[1][0] = 0;
        sprite_delta[1][1] = a;
        ctx->sprite_shift[0] = 0;
        ctx->sprite_shift[1] = 0;
        s->real_sprite_warping_points = 1;
    } else {
        int shift_y = 16 - ctx->sprite_shift[0];
        int shift_c = 16 - ctx->sprite_shift[1];

        for (i = 0; i < 2; i++) {
            if (shift_c < 0 || shift_y < 0 ||
                FFABS(  sprite_offset[0][i]) >= INT_MAX >> shift_y  ||
                FFABS(  sprite_offset[1][i]) >= INT_MAX >> shift_c  ||
                FFABS(   sprite_delta[0][i]) >= INT_MAX >> shift_y  ||
                FFABS(   sprite_delta[1][i]) >= INT_MAX >> shift_y
            ) {
                avpriv_request_sample(s->avctx, "Too large sprite shift, delta or offset");
                goto overflow;
            }
        }

        for (i = 0; i < 2; i++) {
            sprite_offset[0][i]    *= 1 << shift_y;
            sprite_offset[1][i]    *= 1 << shift_c;
            sprite_delta[0][i]     *= 1 << shift_y;
            sprite_delta[1][i]     *= 1 << shift_y;
            ctx->sprite_shift[i]     = 16;

        }
        for (i = 0; i < 2; i++) {
            int64_t sd[2] = {
                sprite_delta[i][0] - a * (1LL<<16),
                sprite_delta[i][1] - a * (1LL<<16)
            };

            if (llabs(sprite_offset[0][i] + sprite_delta[i][0] * (w+16LL)) >= INT_MAX ||
                llabs(sprite_offset[0][i] + sprite_delta[i][1] * (h+16LL)) >= INT_MAX ||
                llabs(sprite_offset[0][i] + sprite_delta[i][0] * (w+16LL) + sprite_delta[i][1] * (h+16LL)) >= INT_MAX ||
                llabs(sprite_delta[i][0] * (w+16LL)) >= INT_MAX ||
                llabs(sprite_delta[i][1] * (h+16LL)) >= INT_MAX ||
                llabs(sd[0]) >= INT_MAX ||
                llabs(sd[1]) >= INT_MAX ||
                llabs(sprite_offset[0][i] + sd[0] * (w+16LL)) >= INT_MAX ||
                llabs(sprite_offset[0][i] + sd[1] * (h+16LL)) >= INT_MAX ||
                llabs(sprite_offset[0][i] + sd[0] * (w+16LL) + sd[1] * (h+16LL)) >= INT_MAX
            ) {
                avpriv_request_sample(s->avctx, "Overflow on sprite points");
                goto overflow;
            }
        }
        s->real_sprite_warping_points = ctx->num_sprite_warping_points;
    }

    for (i = 0; i < 4; i++) {
        s->sprite_offset[i&1][i>>1] = sprite_offset[i&1][i>>1];
        s->sprite_delta [i&1][i>>1] = sprite_delta [i&1][i>>1];
    }

    return 0;
overflow:
    memset(s->sprite_offset, 0, sizeof(s->sprite_offset));
    memset(s->sprite_delta, 0, sizeof(s->sprite_delta));
    return AVERROR_PATCHWELCOME;
}