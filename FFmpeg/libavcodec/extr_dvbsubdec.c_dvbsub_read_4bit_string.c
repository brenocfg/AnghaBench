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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,void* const*,int) ; 

__attribute__((used)) static int dvbsub_read_4bit_string(AVCodecContext *avctx, uint8_t *destbuf, int dbuf_len,
                                   const uint8_t **srcbuf, int buf_size,
                                   int non_mod, uint8_t *map_table, int x_pos)
{
    GetBitContext gb;

    int bits;
    int run_length;
    int pixels_read = x_pos;

    init_get_bits(&gb, *srcbuf, buf_size << 3);

    destbuf += x_pos;

    while (get_bits_count(&gb) < buf_size << 3 && pixels_read < dbuf_len) {
        bits = get_bits(&gb, 4);

        if (bits) {
            if (non_mod != 1 || bits != 1) {
                if (map_table)
                    *destbuf++ = map_table[bits];
                else
                    *destbuf++ = bits;
            }
            pixels_read++;
        } else {
            bits = get_bits1(&gb);
            if (bits == 0) {
                run_length = get_bits(&gb, 3);

                if (run_length == 0) {
                    (*srcbuf) += (get_bits_count(&gb) + 7) >> 3;
                    return pixels_read;
                }

                run_length += 2;

                if (map_table)
                    bits = map_table[0];
                else
                    bits = 0;

                while (run_length-- > 0 && pixels_read < dbuf_len) {
                    *destbuf++ = bits;
                    pixels_read++;
                }
            } else {
                bits = get_bits1(&gb);
                if (bits == 0) {
                    run_length = get_bits(&gb, 2) + 4;
                    bits = get_bits(&gb, 4);

                    if (non_mod == 1 && bits == 1)
                        pixels_read += run_length;
                    else {
                        if (map_table)
                            bits = map_table[bits];
                        while (run_length-- > 0 && pixels_read < dbuf_len) {
                            *destbuf++ = bits;
                            pixels_read++;
                        }
                    }
                } else {
                    bits = get_bits(&gb, 2);
                    if (bits == 2) {
                        run_length = get_bits(&gb, 4) + 9;
                        bits = get_bits(&gb, 4);

                        if (non_mod == 1 && bits == 1)
                            pixels_read += run_length;
                        else {
                            if (map_table)
                                bits = map_table[bits];
                            while (run_length-- > 0 && pixels_read < dbuf_len) {
                                *destbuf++ = bits;
                                pixels_read++;
                            }
                        }
                    } else if (bits == 3) {
                        run_length = get_bits(&gb, 8) + 25;
                        bits = get_bits(&gb, 4);

                        if (non_mod == 1 && bits == 1)
                            pixels_read += run_length;
                        else {
                            if (map_table)
                                bits = map_table[bits];
                            while (run_length-- > 0 && pixels_read < dbuf_len) {
                                *destbuf++ = bits;
                                pixels_read++;
                            }
                        }
                    } else if (bits == 1) {
                        if (map_table)
                            bits = map_table[0];
                        else
                            bits = 0;
                        run_length = 2;
                        while (run_length-- > 0 && pixels_read < dbuf_len) {
                            *destbuf++ = bits;
                            pixels_read++;
                        }
                    } else {
                        if (map_table)
                            bits = map_table[0];
                        else
                            bits = 0;
                        *destbuf++ = bits;
                        pixels_read ++;
                    }
                }
            }
        }
    }

    if (get_bits(&gb, 8))
        av_log(avctx, AV_LOG_ERROR, "line overflow\n");

    (*srcbuf) += (get_bits_count(&gb) + 7) >> 3;

    return pixels_read;
}