#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct TYPE_15__ {int height; TYPE_1__* priv_data; } ;
struct TYPE_14__ {int key_frame; int height; scalar_t__** data; int* linesize; void* decode_error_flags; int /*<<< orphan*/  pict_type; } ;
struct TYPE_13__ {scalar_t__* data; scalar_t__ size; } ;
struct TYPE_12__ {TYPE_3__* frame; } ;
typedef  TYPE_1__ CpiaContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int AV_RL16 (scalar_t__*) ; 
 scalar_t__ COMPRESSED ; 
 scalar_t__ DECIMATION_ENAB ; 
 scalar_t__ EOL ; 
 void* FF_DECODE_ERROR_INVALID_BITSTREAM ; 
 scalar_t__ FRAME_HEADER_SIZE ; 
 scalar_t__ MAGIC_0 ; 
 scalar_t__ MAGIC_1 ; 
 scalar_t__ NOT_COMPRESSED ; 
 scalar_t__ NO_DECIMATION ; 
 scalar_t__ SUBSAMPLE_420 ; 
 scalar_t__ SUBSAMPLE_422 ; 
 scalar_t__ YUVORDER_UYVY ; 
 scalar_t__ YUVORDER_YUYV ; 
 int av_frame_ref (void*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_4__*,char*) ; 
 int ff_reget_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpia_decode_frame(AVCodecContext *avctx,
                             void *data, int *got_frame, AVPacket* avpkt)
{
    CpiaContext* const cpia = avctx->priv_data;
    int i,j,ret;

    uint8_t* const header = avpkt->data;
    uint8_t* src;
    int src_size;
    uint16_t linelength;
    uint8_t skip;

    AVFrame *frame = cpia->frame;
    uint8_t *y, *u, *v, *y_end, *u_end, *v_end;

    // Check header
    if ( avpkt->size < FRAME_HEADER_SIZE + avctx->height * 3
      || header[0] != MAGIC_0 || header[1] != MAGIC_1
      || (header[17] != SUBSAMPLE_420 && header[17] != SUBSAMPLE_422)
      || (header[18] != YUVORDER_YUYV && header[18] != YUVORDER_UYVY)
      || (header[28] != NOT_COMPRESSED && header[28] != COMPRESSED)
      || (header[29] != NO_DECIMATION && header[29] != DECIMATION_ENAB)
    ) {
        av_log(avctx, AV_LOG_ERROR, "Invalid header!\n");
        return AVERROR_INVALIDDATA;
    }

    // currently unsupported properties
    if (header[17] == SUBSAMPLE_422) {
        avpriv_report_missing_feature(avctx, "4:2:2 subsampling");
        return AVERROR_PATCHWELCOME;
    }
    if (header[18] == YUVORDER_UYVY) {
        avpriv_report_missing_feature(avctx, "YUV byte order UYVY");
        return AVERROR_PATCHWELCOME;
    }
    if (header[29] == DECIMATION_ENAB) {
        avpriv_report_missing_feature(avctx, "Decimation");
        return AVERROR_PATCHWELCOME;
    }

    src = header + FRAME_HEADER_SIZE;
    src_size = avpkt->size - FRAME_HEADER_SIZE;

    if (header[28] == NOT_COMPRESSED) {
        frame->pict_type = AV_PICTURE_TYPE_I;
        frame->key_frame = 1;
    } else {
        frame->pict_type = AV_PICTURE_TYPE_P;
        frame->key_frame = 0;
    }

    // Get buffer filled with previous frame
    if ((ret = ff_reget_buffer(avctx, frame, 0)) < 0)
        return ret;


    for ( i = 0;
          i < frame->height;
          i++, src += linelength, src_size -= linelength
    ) {
        // Read line length, two byte little endian
        linelength = AV_RL16(src);
        src += 2;

        if (src_size < linelength) {
            frame->decode_error_flags = FF_DECODE_ERROR_INVALID_BITSTREAM;
            av_log(avctx, AV_LOG_WARNING, "Frame ended unexpectedly!\n");
            break;
        }
        if (src[linelength - 1] != EOL) {
            frame->decode_error_flags = FF_DECODE_ERROR_INVALID_BITSTREAM;
            av_log(avctx, AV_LOG_WARNING, "Wrong line length %d or line not terminated properly (found 0x%02x)!\n", linelength, src[linelength - 1]);
            break;
        }

        /* Update the data pointers. Y data is on every line.
         * U and V data on every second line
         */
        y = &frame->data[0][i * frame->linesize[0]];
        u = &frame->data[1][(i >> 1) * frame->linesize[1]];
        v = &frame->data[2][(i >> 1) * frame->linesize[2]];
        y_end = y + frame->linesize[0] - 1;
        u_end = u + frame->linesize[1] - 1;
        v_end = v + frame->linesize[2] - 1;

        if ((i & 1) && header[17] == SUBSAMPLE_420) {
            /* We are on an odd line and 420 subsample is used.
             * On this line only Y values are specified, one per pixel.
             */
            for (j = 0; j < linelength - 1; j++) {
                if (y > y_end) {
                    frame->decode_error_flags = FF_DECODE_ERROR_INVALID_BITSTREAM;
                    av_log(avctx, AV_LOG_WARNING, "Decoded data exceeded linesize!\n");
                    break;
                }
                if ((src[j] & 1) && header[28] == COMPRESSED) {
                    /* It seems that odd lines are always uncompressed, but
                     * we do it according to specification anyways.
                     */
                    skip = src[j] >> 1;
                    y += skip;
                } else {
                    *(y++) = src[j];
                }
            }
        } else if (header[17] == SUBSAMPLE_420) {
            /* We are on an even line and 420 subsample is used.
             * On this line each pair of pixels is described by four bytes.
             */
            for (j = 0; j < linelength - 4; ) {
                if (y + 1 > y_end || u > u_end || v > v_end) {
                    frame->decode_error_flags = FF_DECODE_ERROR_INVALID_BITSTREAM;
                    av_log(avctx, AV_LOG_WARNING, "Decoded data exceeded linesize!\n");
                    break;
                }
                if ((src[j] & 1) && header[28] == COMPRESSED) {
                    // Skip amount of pixels and move forward one byte
                    skip = src[j] >> 1;
                    y += skip;
                    u += skip >> 1;
                    v += skip >> 1;
                    j++;
                } else {
                    // Set image data as specified and move forward 4 bytes
                    *(y++) = src[j];
                    *(u++) = src[j+1];
                    *(y++) = src[j+2];
                    *(v++) = src[j+3];
                    j += 4;
                }
            }
        }
    }

    *got_frame = 1;
    if ((ret = av_frame_ref(data, cpia->frame)) < 0)
        return ret;

    return avpkt->size;
}