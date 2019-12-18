#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int bits; int /*<<< orphan*/  table; } ;
struct TYPE_9__ {int /*<<< orphan*/  table; } ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
struct TYPE_11__ {TYPE_5__* short_codes; TYPE_5__* long_codes; TYPE_3__ coding_mode; TYPE_5__** filter_coeffs; TYPE_2__ bias; TYPE_1__ filter_params; } ;
typedef  TYPE_4__ VLCSet ;
struct TYPE_12__ {int bits; int /*<<< orphan*/  table; } ;
typedef  TYPE_5__ VLC ;
struct TYPE_13__ {int** channel_data; int filter_params; int filter_bits; int filter_length; unsigned int* bias; int* filter; TYPE_4__* sets; } ;
typedef  TYPE_6__ RALFContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int FILTER_NONE ; 
 int FILTER_RAW ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int av_log2 (int) ; 
 unsigned int extend_code (int /*<<< orphan*/ *,int,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_channel(RALFContext *ctx, GetBitContext *gb, int ch,
                          int length, int mode, int bits)
{
    int i, t;
    int code_params;
    VLCSet *set = ctx->sets + mode;
    VLC *code_vlc; int range, range2, add_bits;
    int *dst = ctx->channel_data[ch];

    ctx->filter_params = get_vlc2(gb, set->filter_params.table, 9, 2);
    if (ctx->filter_params > 1) {
        ctx->filter_bits   = (ctx->filter_params - 2) >> 6;
        ctx->filter_length = ctx->filter_params - (ctx->filter_bits << 6) - 1;
    }

    if (ctx->filter_params == FILTER_RAW) {
        for (i = 0; i < length; i++)
            dst[i] = get_bits(gb, bits);
        ctx->bias[ch] = 0;
        return 0;
    }

    ctx->bias[ch] = get_vlc2(gb, set->bias.table, 9, 2);
    ctx->bias[ch] = extend_code(gb, ctx->bias[ch], 127, 4);

    if (ctx->filter_params == FILTER_NONE) {
        memset(dst, 0, sizeof(*dst) * length);
        return 0;
    }

    if (ctx->filter_params > 1) {
        int cmode = 0, coeff = 0;
        VLC *vlc = set->filter_coeffs[ctx->filter_bits] + 5;

        add_bits = ctx->filter_bits;

        for (i = 0; i < ctx->filter_length; i++) {
            t = get_vlc2(gb, vlc[cmode].table, vlc[cmode].bits, 2);
            t = extend_code(gb, t, 21, add_bits);
            if (!cmode)
                coeff -= 12 << add_bits;
            coeff = t - coeff;
            ctx->filter[i] = coeff;

            cmode = coeff >> add_bits;
            if (cmode < 0) {
                cmode = -1 - av_log2(-cmode);
                if (cmode < -5)
                    cmode = -5;
            } else if (cmode > 0) {
                cmode =  1 + av_log2(cmode);
                if (cmode > 5)
                    cmode = 5;
            }
        }
    }

    code_params = get_vlc2(gb, set->coding_mode.table, set->coding_mode.bits, 2);
    if (code_params >= 15) {
        add_bits = av_clip((code_params / 5 - 3) / 2, 0, 10);
        if (add_bits > 9 && (code_params % 5) != 2)
            add_bits--;
        range    = 10;
        range2   = 21;
        code_vlc = set->long_codes + (code_params - 15);
    } else {
        add_bits = 0;
        range    = 6;
        range2   = 13;
        code_vlc = set->short_codes + code_params;
    }

    for (i = 0; i < length; i += 2) {
        int code1, code2;

        t = get_vlc2(gb, code_vlc->table, code_vlc->bits, 2);
        code1 = t / range2;
        code2 = t % range2;
        dst[i]     = extend_code(gb, code1, range, 0) * (1U << add_bits);
        dst[i + 1] = extend_code(gb, code2, range, 0) * (1U << add_bits);
        if (add_bits) {
            dst[i]     |= get_bits(gb, add_bits);
            dst[i + 1] |= get_bits(gb, add_bits);
        }
    }

    return 0;
}