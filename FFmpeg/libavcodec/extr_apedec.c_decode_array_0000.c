#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_6__ {int error; int /*<<< orphan*/  gb; } ;
struct TYPE_5__ {int ksum; int k; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ APERice ;
typedef  TYPE_2__ APEContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 void* av_log2 (int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_rice_ook (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void decode_array_0000(APEContext *ctx, GetBitContext *gb,
                              int32_t *out, APERice *rice, int blockstodecode)
{
    int i;
    unsigned ksummax, ksummin;

    rice->ksum = 0;
    for (i = 0; i < FFMIN(blockstodecode, 5); i++) {
        out[i] = get_rice_ook(&ctx->gb, 10);
        rice->ksum += out[i];
    }
    rice->k = av_log2(rice->ksum / 10) + 1;
    if (rice->k >= 24)
        return;
    for (; i < FFMIN(blockstodecode, 64); i++) {
        out[i] = get_rice_ook(&ctx->gb, rice->k);
        rice->ksum += out[i];
        rice->k = av_log2(rice->ksum / ((i + 1) * 2)) + 1;
        if (rice->k >= 24)
            return;
    }
    ksummax = 1 << rice->k + 7;
    ksummin = rice->k ? (1 << rice->k + 6) : 0;
    for (; i < blockstodecode; i++) {
        if (get_bits_left(&ctx->gb) < 1) {
            ctx->error = 1;
            return ;
        }
        out[i] = get_rice_ook(&ctx->gb, rice->k);
        rice->ksum += out[i] - out[i - 64];
        while (rice->ksum < ksummin) {
            rice->k--;
            ksummin = rice->k ? ksummin >> 1 : 0;
            ksummax >>= 1;
        }
        while (rice->ksum >= ksummax) {
            rice->k++;
            if (rice->k > 24)
                return;
            ksummax <<= 1;
            ksummin = ksummin ? ksummin << 1 : 128;
        }
    }

    for (i = 0; i < blockstodecode; i++)
        out[i] = ((out[i] >> 1) ^ ((out[i] & 1) - 1)) + 1;
}