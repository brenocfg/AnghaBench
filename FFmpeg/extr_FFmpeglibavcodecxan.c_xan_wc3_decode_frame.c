#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int* buffer1; int buffer1_size; int* buffer2; int size; int* buf; int buffer2_size; TYPE_5__* avctx; } ;
typedef  TYPE_1__ XanContext ;
struct TYPE_7__ {int width; int height; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RL16 (int*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_be24 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int*,int) ; 
 int sign_extend (int,int) ; 
 int xan_huffman_decode (int*,int,int const*,int) ; 
 int /*<<< orphan*/  xan_unpack (int*,int,int const*,int) ; 
 int /*<<< orphan*/  xan_wc3_copy_pixel_run (TYPE_1__*,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  xan_wc3_output_pixel_run (TYPE_1__*,int /*<<< orphan*/ *,int const*,int,int,int) ; 

__attribute__((used)) static int xan_wc3_decode_frame(XanContext *s, AVFrame *frame)
{

    int width  = s->avctx->width;
    int height = s->avctx->height;
    int total_pixels = width * height;
    uint8_t opcode;
    uint8_t flag = 0;
    int size = 0;
    int motion_x, motion_y;
    int x, y, ret;

    uint8_t *opcode_buffer = s->buffer1;
    uint8_t *opcode_buffer_end = s->buffer1 + s->buffer1_size;
    int opcode_buffer_size = s->buffer1_size;
    const uint8_t *imagedata_buffer = s->buffer2;

    /* pointers to segments inside the compressed chunk */
    const uint8_t *huffman_segment;
    GetByteContext       size_segment;
    GetByteContext       vector_segment;
    const uint8_t *imagedata_segment;
    int huffman_offset, size_offset, vector_offset, imagedata_offset,
        imagedata_size;

    if (s->size < 8)
        return AVERROR_INVALIDDATA;

    huffman_offset    = AV_RL16(&s->buf[0]);
    size_offset       = AV_RL16(&s->buf[2]);
    vector_offset     = AV_RL16(&s->buf[4]);
    imagedata_offset  = AV_RL16(&s->buf[6]);

    if (huffman_offset   >= s->size ||
        size_offset      >= s->size ||
        vector_offset    >= s->size ||
        imagedata_offset >= s->size)
        return AVERROR_INVALIDDATA;

    huffman_segment   = s->buf + huffman_offset;
    bytestream2_init(&size_segment,   s->buf + size_offset,   s->size - size_offset);
    bytestream2_init(&vector_segment, s->buf + vector_offset, s->size - vector_offset);
    imagedata_segment = s->buf + imagedata_offset;

    if ((ret = xan_huffman_decode(opcode_buffer, opcode_buffer_size,
                                  huffman_segment, s->size - huffman_offset)) < 0)
        return AVERROR_INVALIDDATA;
    opcode_buffer_end = opcode_buffer + ret;

    if (imagedata_segment[0] == 2) {
        xan_unpack(s->buffer2, s->buffer2_size,
                   &imagedata_segment[1], s->size - imagedata_offset - 1);
        imagedata_size = s->buffer2_size;
    } else {
        imagedata_size = s->size - imagedata_offset - 1;
        imagedata_buffer = &imagedata_segment[1];
    }

    /* use the decoded data segments to build the frame */
    x = y = 0;
    while (total_pixels && opcode_buffer < opcode_buffer_end) {

        opcode = *opcode_buffer++;
        size = 0;

        switch (opcode) {

        case 0:
            flag ^= 1;
            continue;

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            size = opcode;
            break;

        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            size += (opcode - 10);
            break;

        case 9:
        case 19:
            if (bytestream2_get_bytes_left(&size_segment) < 1) {
                av_log(s->avctx, AV_LOG_ERROR, "size_segment overread\n");
                return AVERROR_INVALIDDATA;
            }
            size = bytestream2_get_byte(&size_segment);
            break;

        case 10:
        case 20:
            if (bytestream2_get_bytes_left(&size_segment) < 2) {
                av_log(s->avctx, AV_LOG_ERROR, "size_segment overread\n");
                return AVERROR_INVALIDDATA;
            }
            size = bytestream2_get_be16(&size_segment);
            break;

        case 11:
        case 21:
            if (bytestream2_get_bytes_left(&size_segment) < 3) {
                av_log(s->avctx, AV_LOG_ERROR, "size_segment overread\n");
                return AVERROR_INVALIDDATA;
            }
            size = bytestream2_get_be24(&size_segment);
            break;
        }

        if (size > total_pixels)
            break;

        if (opcode < 12) {
            flag ^= 1;
            if (flag) {
                /* run of (size) pixels is unchanged from last frame */
                xan_wc3_copy_pixel_run(s, frame, x, y, size, 0, 0);
            } else {
                /* output a run of pixels from imagedata_buffer */
                if (imagedata_size < size)
                    break;
                xan_wc3_output_pixel_run(s, frame, imagedata_buffer, x, y, size);
                imagedata_buffer += size;
                imagedata_size -= size;
            }
        } else {
            uint8_t vector;
            if (bytestream2_get_bytes_left(&vector_segment) <= 0) {
                av_log(s->avctx, AV_LOG_ERROR, "vector_segment overread\n");
                return AVERROR_INVALIDDATA;
            }
            /* run-based motion compensation from last frame */
            vector = bytestream2_get_byte(&vector_segment);
            motion_x = sign_extend(vector >> 4,  4);
            motion_y = sign_extend(vector & 0xF, 4);

            /* copy a run of pixels from the previous frame */
            xan_wc3_copy_pixel_run(s, frame, x, y, size, motion_x, motion_y);

            flag = 0;
        }

        /* coordinate accounting */
        total_pixels -= size;
        y += (x + size) / width;
        x  = (x + size) % width;
    }
    return 0;
}