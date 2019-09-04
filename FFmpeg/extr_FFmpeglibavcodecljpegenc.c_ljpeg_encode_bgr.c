#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_14__ {scalar_t__ pix_fmt; TYPE_2__* priv_data; } ;
struct TYPE_13__ {int width; int height; int* linesize; int** data; } ;
struct TYPE_12__ {int pred; int /*<<< orphan*/  huff_code_dc_chrominance; int /*<<< orphan*/  huff_size_dc_chrominance; int /*<<< orphan*/  huff_code_dc_luminance; int /*<<< orphan*/  huff_size_dc_luminance; int /*<<< orphan*/  scratch; } ;
struct TYPE_11__ {int const buf_end; int const buf; } ;
typedef  TYPE_1__ PutBitContext ;
typedef  TYPE_2__ LJpegEncContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_BGR24 ; 
 scalar_t__ AV_PIX_FMT_BGRA ; 
 int /*<<< orphan*/  PREDICT (int,int,int,int,int const) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int** buffer ; 
 int /*<<< orphan*/  ff_mjpeg_encode_dc (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int put_bits_count (TYPE_1__*) ; 
 int /*<<< orphan*/ * uint16_t (int*) ; 

__attribute__((used)) static int ljpeg_encode_bgr(AVCodecContext *avctx, PutBitContext *pb,
                            const AVFrame *frame)
{
    LJpegEncContext *s    = avctx->priv_data;
    const int width       = frame->width;
    const int height      = frame->height;
    const int linesize    = frame->linesize[0];
    uint16_t (*buffer)[4] = s->scratch;
    int left[4], top[4], topleft[4];
    int x, y, i;

#if FF_API_PRIVATE_OPT
FF_DISABLE_DEPRECATION_WARNINGS
    if (avctx->prediction_method)
        s->pred = avctx->prediction_method + 1;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    for (i = 0; i < 4; i++)
        buffer[0][i] = 1 << (9 - 1);

    for (y = 0; y < height; y++) {
        const int modified_predictor = y ? s->pred : 1;
        uint8_t *ptr = frame->data[0] + (linesize * y);

        if (pb->buf_end - pb->buf - (put_bits_count(pb) >> 3) < width * 4 * 4) {
            av_log(avctx, AV_LOG_ERROR, "encoded frame too large\n");
            return -1;
        }

        for (i = 0; i < 4; i++)
            top[i]= left[i]= topleft[i]= buffer[0][i];

        for (x = 0; x < width; x++) {
            if(avctx->pix_fmt == AV_PIX_FMT_BGR24){
                buffer[x][1] =  ptr[3 * x + 0] -     ptr[3 * x + 1] + 0x100;
                buffer[x][2] =  ptr[3 * x + 2] -     ptr[3 * x + 1] + 0x100;
                buffer[x][0] = (ptr[3 * x + 0] + 2 * ptr[3 * x + 1] + ptr[3 * x + 2]) >> 2;
            }else{
                buffer[x][1] =  ptr[4 * x + 0] -     ptr[4 * x + 1] + 0x100;
                buffer[x][2] =  ptr[4 * x + 2] -     ptr[4 * x + 1] + 0x100;
                buffer[x][0] = (ptr[4 * x + 0] + 2 * ptr[4 * x + 1] + ptr[4 * x + 2]) >> 2;
                if (avctx->pix_fmt == AV_PIX_FMT_BGRA)
                    buffer[x][3] =  ptr[4 * x + 3];
            }

            for (i = 0; i < 3 + (avctx->pix_fmt == AV_PIX_FMT_BGRA); i++) {
                int pred, diff;

                PREDICT(pred, topleft[i], top[i], left[i], modified_predictor);

                topleft[i] = top[i];
                top[i]     = buffer[x+1][i];

                left[i]    = buffer[x][i];

                diff       = ((left[i] - pred + 0x100) & 0x1FF) - 0x100;

                if (i == 0 || i == 3)
                    ff_mjpeg_encode_dc(pb, diff, s->huff_size_dc_luminance, s->huff_code_dc_luminance); //FIXME ugly
                else
                    ff_mjpeg_encode_dc(pb, diff, s->huff_size_dc_chrominance, s->huff_code_dc_chrominance);
            }
        }
    }

    return 0;
}