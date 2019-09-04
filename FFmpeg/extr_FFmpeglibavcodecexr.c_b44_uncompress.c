#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int int8_t ;
struct TYPE_9__ {int nb_channels; TYPE_1__* channels; } ;
struct TYPE_8__ {int xsize; int ysize; int channel_line_size; int* uncompressed_data; } ;
struct TYPE_7__ {scalar_t__ pixel_type; } ;
typedef  TYPE_2__ EXRThreadData ;
typedef  TYPE_3__ EXRContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ EXR_HALF ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  unpack_14 (int const*,int*) ; 
 int /*<<< orphan*/  unpack_3 (int const*,int*) ; 

__attribute__((used)) static int b44_uncompress(EXRContext *s, const uint8_t *src, int compressed_size,
                          int uncompressed_size, EXRThreadData *td) {
    const int8_t *sr = src;
    int stay_to_uncompress = compressed_size;
    int nb_b44_block_w, nb_b44_block_h;
    int index_tl_x, index_tl_y, index_out, index_tmp;
    uint16_t tmp_buffer[16]; /* B44 use 4x4 half float pixel */
    int c, iY, iX, y, x;
    int target_channel_offset = 0;

    /* calc B44 block count */
    nb_b44_block_w = td->xsize / 4;
    if ((td->xsize % 4) != 0)
        nb_b44_block_w++;

    nb_b44_block_h = td->ysize / 4;
    if ((td->ysize % 4) != 0)
        nb_b44_block_h++;

    for (c = 0; c < s->nb_channels; c++) {
        if (s->channels[c].pixel_type == EXR_HALF) {/* B44 only compress half float data */
            for (iY = 0; iY < nb_b44_block_h; iY++) {
                for (iX = 0; iX < nb_b44_block_w; iX++) {/* For each B44 block */
                    if (stay_to_uncompress < 3) {
                        av_log(s, AV_LOG_ERROR, "Not enough data for B44A block: %d", stay_to_uncompress);
                        return AVERROR_INVALIDDATA;
                    }

                    if (src[compressed_size - stay_to_uncompress + 2] == 0xfc) { /* B44A block */
                        unpack_3(sr, tmp_buffer);
                        sr += 3;
                        stay_to_uncompress -= 3;
                    }  else {/* B44 Block */
                        if (stay_to_uncompress < 14) {
                            av_log(s, AV_LOG_ERROR, "Not enough data for B44 block: %d", stay_to_uncompress);
                            return AVERROR_INVALIDDATA;
                        }
                        unpack_14(sr, tmp_buffer);
                        sr += 14;
                        stay_to_uncompress -= 14;
                    }

                    /* copy data to uncompress buffer (B44 block can exceed target resolution)*/
                    index_tl_x = iX * 4;
                    index_tl_y = iY * 4;

                    for (y = index_tl_y; y < FFMIN(index_tl_y + 4, td->ysize); y++) {
                        for (x = index_tl_x; x < FFMIN(index_tl_x + 4, td->xsize); x++) {
                            index_out = target_channel_offset * td->xsize + y * td->channel_line_size + 2 * x;
                            index_tmp = (y-index_tl_y) * 4 + (x-index_tl_x);
                            td->uncompressed_data[index_out] = tmp_buffer[index_tmp] & 0xff;
                            td->uncompressed_data[index_out + 1] = tmp_buffer[index_tmp] >> 8;
                        }
                    }
                }
            }
            target_channel_offset += 2;
        } else {/* Float or UINT 32 channel */
            if (stay_to_uncompress < td->ysize * td->xsize * 4) {
                av_log(s, AV_LOG_ERROR, "Not enough data for uncompress channel: %d", stay_to_uncompress);
                return AVERROR_INVALIDDATA;
            }

            for (y = 0; y < td->ysize; y++) {
                index_out = target_channel_offset * td->xsize + y * td->channel_line_size;
                memcpy(&td->uncompressed_data[index_out], sr, td->xsize * 4);
                sr += td->xsize * 4;
            }
            target_channel_offset += 4;

            stay_to_uncompress -= td->ysize * td->xsize * 4;
        }
    }

    return 0;
}