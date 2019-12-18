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
typedef  int int16_t ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct TYPE_5__ {int last_dc; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; TYPE_1__ pre_vlc; int /*<<< orphan*/  pre_gb; } ;
typedef  TYPE_2__ FourXContext ;

/* Variables and functions */
 int /*<<< orphan*/  ACDC_VLC_BITS ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int* dequant_table ; 
 int* ff_zigzag_direct ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int get_xbits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_i_block(FourXContext *f, int16_t *block)
{
    int code, i, j, level, val;

    if (get_bits_left(&f->gb) < 2){
        av_log(f->avctx, AV_LOG_ERROR, "%d bits left before decode_i_block()\n", get_bits_left(&f->gb));
        return AVERROR_INVALIDDATA;
    }

    /* DC coef */
    val = get_vlc2(&f->pre_gb, f->pre_vlc.table, ACDC_VLC_BITS, 3);
    if (val >> 4) {
        av_log(f->avctx, AV_LOG_ERROR, "error dc run != 0\n");
        return AVERROR_INVALIDDATA;
    }

    if (val)
        val = get_xbits(&f->gb, val);

    val        = val * dequant_table[0] + f->last_dc;
    f->last_dc = block[0] = val;
    /* AC coefs */
    i = 1;
    for (;;) {
        code = get_vlc2(&f->pre_gb, f->pre_vlc.table, ACDC_VLC_BITS, 3);

        /* EOB */
        if (code == 0)
            break;
        if (code == 0xf0) {
            i += 16;
            if (i >= 64) {
                av_log(f->avctx, AV_LOG_ERROR, "run %d overflow\n", i);
                return 0;
            }
        } else {
            if (code & 0xf) {
                level = get_xbits(&f->gb, code & 0xf);
            } else {
                av_log(f->avctx, AV_LOG_ERROR, "0 coeff\n");
                return AVERROR_INVALIDDATA;
            }
            i    += code >> 4;
            if (i >= 64) {
                av_log(f->avctx, AV_LOG_ERROR, "run %d overflow\n", i);
                return 0;
            }

            j = ff_zigzag_direct[i];
            block[j] = level * dequant_table[j];
            i++;
            if (i >= 64)
                break;
        }
    }

    return 0;
}