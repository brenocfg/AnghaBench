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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int* linesize; int bits; int nb_components; int v_max; int h_max; int** ljpeg_buffer; int mb_width; int mb_height; int* comp_index; scalar_t__ pegasus_rct; scalar_t__ rct; int /*<<< orphan*/  gb; scalar_t__ restart_count; scalar_t__ restart_interval; int /*<<< orphan*/ * dc_index; int /*<<< orphan*/  avctx; scalar_t__ bottom_field; scalar_t__ interlaced; TYPE_1__* picture_ptr; int /*<<< orphan*/  ljpeg_buffer_size; int /*<<< orphan*/  lossless; } ;
struct TYPE_5__ {int** data; } ;
typedef  TYPE_2__ MJpegDecodeContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  PREDICT (int,int,int,int,int) ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fast_malloc (int***,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int mjpeg_decode_dc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ljpeg_decode_rgb_scan(MJpegDecodeContext *s, int nb_components, int predictor, int point_transform)
{
    int i, mb_x, mb_y;
    uint16_t (*buffer)[4];
    int left[4], top[4], topleft[4];
    const int linesize = s->linesize[0];
    const int mask     = ((1 << s->bits) - 1) << point_transform;
    int resync_mb_y = 0;
    int resync_mb_x = 0;

    if (s->nb_components != 3 && s->nb_components != 4)
        return AVERROR_INVALIDDATA;
    if (s->v_max != 1 || s->h_max != 1 || !s->lossless)
        return AVERROR_INVALIDDATA;


    s->restart_count = s->restart_interval;

    av_fast_malloc(&s->ljpeg_buffer, &s->ljpeg_buffer_size,
                   (unsigned)s->mb_width * 4 * sizeof(s->ljpeg_buffer[0][0]));
    if (!s->ljpeg_buffer)
        return AVERROR(ENOMEM);

    buffer = s->ljpeg_buffer;

    for (i = 0; i < 4; i++)
        buffer[0][i] = 1 << (s->bits - 1);

    for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
        uint8_t *ptr = s->picture_ptr->data[0] + (linesize * mb_y);

        if (s->interlaced && s->bottom_field)
            ptr += linesize >> 1;

        for (i = 0; i < 4; i++)
            top[i] = left[i] = topleft[i] = buffer[0][i];

        for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
            int modified_predictor = predictor;

            if (get_bits_left(&s->gb) < 1) {
                av_log(s->avctx, AV_LOG_ERROR, "bitstream end in rgb_scan\n");
                return AVERROR_INVALIDDATA;
            }

            if (s->restart_interval && !s->restart_count){
                s->restart_count = s->restart_interval;
                resync_mb_x = mb_x;
                resync_mb_y = mb_y;
                for(i=0; i<4; i++)
                    top[i] = left[i]= topleft[i]= 1 << (s->bits - 1);
            }
            if (mb_y == resync_mb_y || mb_y == resync_mb_y+1 && mb_x < resync_mb_x || !mb_x)
                modified_predictor = 1;

            for (i=0;i<nb_components;i++) {
                int pred, dc;

                topleft[i] = top[i];
                top[i]     = buffer[mb_x][i];

                PREDICT(pred, topleft[i], top[i], left[i], modified_predictor);

                dc = mjpeg_decode_dc(s, s->dc_index[i]);
                if(dc == 0xFFFFF)
                    return -1;

                left[i] = buffer[mb_x][i] =
                    mask & (pred + (unsigned)(dc * (1 << point_transform)));
            }

            if (s->restart_interval && !--s->restart_count) {
                align_get_bits(&s->gb);
                skip_bits(&s->gb, 16); /* skip RSTn */
            }
        }
        if (s->rct && s->nb_components == 4) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                ptr[4*mb_x + 2] = buffer[mb_x][0] - ((buffer[mb_x][1] + buffer[mb_x][2] - 0x200) >> 2);
                ptr[4*mb_x + 1] = buffer[mb_x][1] + ptr[4*mb_x + 2];
                ptr[4*mb_x + 3] = buffer[mb_x][2] + ptr[4*mb_x + 2];
                ptr[4*mb_x + 0] = buffer[mb_x][3];
            }
        } else if (s->nb_components == 4) {
            for(i=0; i<nb_components; i++) {
                int c= s->comp_index[i];
                if (s->bits <= 8) {
                    for(mb_x = 0; mb_x < s->mb_width; mb_x++) {
                        ptr[4*mb_x+3-c] = buffer[mb_x][i];
                    }
                } else if(s->bits == 9) {
                    return AVERROR_PATCHWELCOME;
                } else {
                    for(mb_x = 0; mb_x < s->mb_width; mb_x++) {
                        ((uint16_t*)ptr)[4*mb_x+c] = buffer[mb_x][i];
                    }
                }
            }
        } else if (s->rct) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                ptr[3*mb_x + 1] = buffer[mb_x][0] - ((buffer[mb_x][1] + buffer[mb_x][2] - 0x200) >> 2);
                ptr[3*mb_x + 0] = buffer[mb_x][1] + ptr[3*mb_x + 1];
                ptr[3*mb_x + 2] = buffer[mb_x][2] + ptr[3*mb_x + 1];
            }
        } else if (s->pegasus_rct) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                ptr[3*mb_x + 1] = buffer[mb_x][0] - ((buffer[mb_x][1] + buffer[mb_x][2]) >> 2);
                ptr[3*mb_x + 0] = buffer[mb_x][1] + ptr[3*mb_x + 1];
                ptr[3*mb_x + 2] = buffer[mb_x][2] + ptr[3*mb_x + 1];
            }
        } else {
            for(i=0; i<nb_components; i++) {
                int c= s->comp_index[i];
                if (s->bits <= 8) {
                    for(mb_x = 0; mb_x < s->mb_width; mb_x++) {
                        ptr[3*mb_x+2-c] = buffer[mb_x][i];
                    }
                } else if(s->bits == 9) {
                    return AVERROR_PATCHWELCOME;
                } else {
                    for(mb_x = 0; mb_x < s->mb_width; mb_x++) {
                        ((uint16_t*)ptr)[3*mb_x+2-c] = buffer[mb_x][i];
                    }
                }
            }
        }
    }
    return 0;
}