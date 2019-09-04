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
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dvbsub_read_8bit_string(AVCodecContext *avctx,
                                   uint8_t *destbuf, int dbuf_len,
                                    const uint8_t **srcbuf, int buf_size,
                                    int non_mod, uint8_t *map_table, int x_pos)
{
    const uint8_t *sbuf_end = (*srcbuf) + buf_size;
    int bits;
    int run_length;
    int pixels_read = x_pos;

    destbuf += x_pos;

    while (*srcbuf < sbuf_end && pixels_read < dbuf_len) {
        bits = *(*srcbuf)++;

        if (bits) {
            if (non_mod != 1 || bits != 1) {
                if (map_table)
                    *destbuf++ = map_table[bits];
                else
                    *destbuf++ = bits;
            }
            pixels_read++;
        } else {
            bits = *(*srcbuf)++;
            run_length = bits & 0x7f;
            if ((bits & 0x80) == 0) {
                if (run_length == 0) {
                    return pixels_read;
                }

                bits = 0;
            } else {
                bits = *(*srcbuf)++;
            }
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
        }
    }

    if (*(*srcbuf)++)
        av_log(avctx, AV_LOG_ERROR, "line overflow\n");

    return pixels_read;
}