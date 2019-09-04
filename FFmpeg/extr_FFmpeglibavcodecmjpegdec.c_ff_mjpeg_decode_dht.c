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
typedef  int uint8_t ;
struct TYPE_3__ {int*** raw_huffman_lengths; int*** raw_huffman_values; int /*<<< orphan*/ ** vlcs; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ MJpegDecodeContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int build_vlc (int /*<<< orphan*/ *,int*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_free_vlc (int /*<<< orphan*/ *) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

int ff_mjpeg_decode_dht(MJpegDecodeContext *s)
{
    int len, index, i, class, n, v, code_max;
    uint8_t bits_table[17];
    uint8_t val_table[256];
    int ret = 0;

    len = get_bits(&s->gb, 16) - 2;

    if (8*len > get_bits_left(&s->gb)) {
        av_log(s->avctx, AV_LOG_ERROR, "dht: len %d is too large\n", len);
        return AVERROR_INVALIDDATA;
    }

    while (len > 0) {
        if (len < 17)
            return AVERROR_INVALIDDATA;
        class = get_bits(&s->gb, 4);
        if (class >= 2)
            return AVERROR_INVALIDDATA;
        index = get_bits(&s->gb, 4);
        if (index >= 4)
            return AVERROR_INVALIDDATA;
        n = 0;
        for (i = 1; i <= 16; i++) {
            bits_table[i] = get_bits(&s->gb, 8);
            n += bits_table[i];
        }
        len -= 17;
        if (len < n || n > 256)
            return AVERROR_INVALIDDATA;

        code_max = 0;
        for (i = 0; i < n; i++) {
            v = get_bits(&s->gb, 8);
            if (v > code_max)
                code_max = v;
            val_table[i] = v;
        }
        len -= n;

        /* build VLC and flush previous vlc if present */
        ff_free_vlc(&s->vlcs[class][index]);
        av_log(s->avctx, AV_LOG_DEBUG, "class=%d index=%d nb_codes=%d\n",
               class, index, code_max + 1);
        if ((ret = build_vlc(&s->vlcs[class][index], bits_table, val_table,
                             code_max + 1, 0, class > 0)) < 0)
            return ret;

        if (class > 0) {
            ff_free_vlc(&s->vlcs[2][index]);
            if ((ret = build_vlc(&s->vlcs[2][index], bits_table, val_table,
                                 code_max + 1, 0, 0)) < 0)
                return ret;
        }

        for (i = 0; i < 16; i++)
            s->raw_huffman_lengths[class][index][i] = bits_table[i + 1];
        for (i = 0; i < 256; i++)
            s->raw_huffman_values[class][index][i] = val_table[i];
    }
    return 0;
}