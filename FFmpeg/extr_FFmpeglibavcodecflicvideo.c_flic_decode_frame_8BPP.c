#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {unsigned char** data; unsigned int* linesize; int palette_has_changed; } ;
struct TYPE_11__ {TYPE_2__* priv_data; } ;
struct TYPE_10__ {unsigned int* palette; int new_palette; TYPE_6__* frame; TYPE_1__* avctx; int /*<<< orphan*/  fli_type; } ;
struct TYPE_9__ {unsigned int height; int width; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ FlicDecodeContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  CHECK_PIXEL_PTR (int) ; 
 unsigned int FFALIGN (int,int) ; 
 int /*<<< orphan*/  FLC_MAGIC_CARPET_SYNTHETIC_TYPE_CODE ; 
#define  FLI_256_COLOR 135 
#define  FLI_BLACK 134 
#define  FLI_BRUN 133 
#define  FLI_COLOR 132 
#define  FLI_COPY 131 
#define  FLI_DELTA 130 
#define  FLI_LC 129 
#define  FLI_MINI 128 
 int INT_MAX ; 
 int av_frame_ref (void*,TYPE_6__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 unsigned int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int ff_reget_buffer (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int sign_extend (int,int) ; 

__attribute__((used)) static int flic_decode_frame_8BPP(AVCodecContext *avctx,
                                  void *data, int *got_frame,
                                  const uint8_t *buf, int buf_size)
{
    FlicDecodeContext *s = avctx->priv_data;

    GetByteContext g2;
    int pixel_ptr;
    int palette_ptr;
    unsigned char palette_idx1;
    unsigned char palette_idx2;

    unsigned int frame_size;
    int num_chunks;

    unsigned int chunk_size;
    int chunk_type;

    int i, j, ret;

    int color_packets;
    int color_changes;
    int color_shift;
    unsigned char r, g, b;

    int lines;
    int compressed_lines;
    int starting_line;
    signed short line_packets;
    int y_ptr;
    int byte_run;
    int pixel_skip;
    int pixel_countdown;
    unsigned char *pixels;
    unsigned int pixel_limit;

    bytestream2_init(&g2, buf, buf_size);

    if ((ret = ff_reget_buffer(avctx, s->frame)) < 0)
        return ret;

    pixels = s->frame->data[0];
    pixel_limit = s->avctx->height * s->frame->linesize[0];
    if (buf_size < 16 || buf_size > INT_MAX - (3 * 256 + AV_INPUT_BUFFER_PADDING_SIZE))
        return AVERROR_INVALIDDATA;
    frame_size = bytestream2_get_le32(&g2);
    if (frame_size > buf_size)
        frame_size = buf_size;
    bytestream2_skip(&g2, 2); /* skip the magic number */
    num_chunks = bytestream2_get_le16(&g2);
    bytestream2_skip(&g2, 8);  /* skip padding */

    if (frame_size < 16)
        return AVERROR_INVALIDDATA;

    frame_size -= 16;

    /* iterate through the chunks */
    while ((frame_size >= 6) && (num_chunks > 0) &&
            bytestream2_get_bytes_left(&g2) >= 4) {
        int stream_ptr_after_chunk;
        chunk_size = bytestream2_get_le32(&g2);
        if (chunk_size > frame_size) {
            av_log(avctx, AV_LOG_WARNING,
                   "Invalid chunk_size = %u > frame_size = %u\n", chunk_size, frame_size);
            chunk_size = frame_size;
        }
        stream_ptr_after_chunk = bytestream2_tell(&g2) - 4 + chunk_size;

        chunk_type = bytestream2_get_le16(&g2);

        switch (chunk_type) {
        case FLI_256_COLOR:
        case FLI_COLOR:
            /* check special case: If this file is from the Magic Carpet
             * game and uses 6-bit colors even though it reports 256-color
             * chunks in a 0xAF12-type file (fli_type is set to 0xAF13 during
             * initialization) */
            if ((chunk_type == FLI_256_COLOR) && (s->fli_type != FLC_MAGIC_CARPET_SYNTHETIC_TYPE_CODE))
                color_shift = 0;
            else
                color_shift = 2;
            /* set up the palette */
            color_packets = bytestream2_get_le16(&g2);
            palette_ptr = 0;
            for (i = 0; i < color_packets; i++) {
                /* first byte is how many colors to skip */
                palette_ptr += bytestream2_get_byte(&g2);

                /* next byte indicates how many entries to change */
                color_changes = bytestream2_get_byte(&g2);

                /* if there are 0 color changes, there are actually 256 */
                if (color_changes == 0)
                    color_changes = 256;

                if (bytestream2_tell(&g2) + color_changes * 3 > stream_ptr_after_chunk)
                    break;

                for (j = 0; j < color_changes; j++) {
                    unsigned int entry;

                    /* wrap around, for good measure */
                    if ((unsigned)palette_ptr >= 256)
                        palette_ptr = 0;

                    r = bytestream2_get_byte(&g2) << color_shift;
                    g = bytestream2_get_byte(&g2) << color_shift;
                    b = bytestream2_get_byte(&g2) << color_shift;
                    entry = 0xFFU << 24 | r << 16 | g << 8 | b;
                    if (color_shift == 2)
                        entry |= entry >> 6 & 0x30303;
                    if (s->palette[palette_ptr] != entry)
                        s->new_palette = 1;
                    s->palette[palette_ptr++] = entry;
                }
            }
            break;

        case FLI_DELTA:
            y_ptr = 0;
            compressed_lines = bytestream2_get_le16(&g2);
            while (compressed_lines > 0) {
                if (bytestream2_tell(&g2) + 2 > stream_ptr_after_chunk)
                    break;
                if (y_ptr > pixel_limit)
                    return AVERROR_INVALIDDATA;
                line_packets = bytestream2_get_le16(&g2);
                if ((line_packets & 0xC000) == 0xC000) {
                    // line skip opcode
                    line_packets = -line_packets;
                    if (line_packets > s->avctx->height)
                        return AVERROR_INVALIDDATA;
                    y_ptr += line_packets * s->frame->linesize[0];
                } else if ((line_packets & 0xC000) == 0x4000) {
                    av_log(avctx, AV_LOG_ERROR, "Undefined opcode (%x) in DELTA_FLI\n", line_packets);
                } else if ((line_packets & 0xC000) == 0x8000) {
                    // "last byte" opcode
                    pixel_ptr= y_ptr + s->frame->linesize[0] - 1;
                    CHECK_PIXEL_PTR(0);
                    pixels[pixel_ptr] = line_packets & 0xff;
                } else {
                    compressed_lines--;
                    pixel_ptr = y_ptr;
                    CHECK_PIXEL_PTR(0);
                    pixel_countdown = s->avctx->width;
                    for (i = 0; i < line_packets; i++) {
                        if (bytestream2_tell(&g2) + 2 > stream_ptr_after_chunk)
                            break;
                        /* account for the skip bytes */
                        pixel_skip = bytestream2_get_byte(&g2);
                        pixel_ptr += pixel_skip;
                        pixel_countdown -= pixel_skip;
                        byte_run = sign_extend(bytestream2_get_byte(&g2), 8);
                        if (byte_run < 0) {
                            byte_run = -byte_run;
                            palette_idx1 = bytestream2_get_byte(&g2);
                            palette_idx2 = bytestream2_get_byte(&g2);
                            CHECK_PIXEL_PTR(byte_run * 2);
                            for (j = 0; j < byte_run; j++, pixel_countdown -= 2) {
                                pixels[pixel_ptr++] = palette_idx1;
                                pixels[pixel_ptr++] = palette_idx2;
                            }
                        } else {
                            CHECK_PIXEL_PTR(byte_run * 2);
                            if (bytestream2_tell(&g2) + byte_run * 2 > stream_ptr_after_chunk)
                                break;
                            for (j = 0; j < byte_run * 2; j++, pixel_countdown--) {
                                pixels[pixel_ptr++] = bytestream2_get_byte(&g2);
                            }
                        }
                    }

                    y_ptr += s->frame->linesize[0];
                }
            }
            break;

        case FLI_LC:
            /* line compressed */
            starting_line = bytestream2_get_le16(&g2);
            if (starting_line >= s->avctx->height)
                return AVERROR_INVALIDDATA;
            y_ptr = 0;
            y_ptr += starting_line * s->frame->linesize[0];

            compressed_lines = bytestream2_get_le16(&g2);
            while (compressed_lines > 0) {
                pixel_ptr = y_ptr;
                CHECK_PIXEL_PTR(0);
                pixel_countdown = s->avctx->width;
                if (bytestream2_tell(&g2) + 1 > stream_ptr_after_chunk)
                    break;
                line_packets = bytestream2_get_byte(&g2);
                if (line_packets > 0) {
                    for (i = 0; i < line_packets; i++) {
                        /* account for the skip bytes */
                        if (bytestream2_tell(&g2) + 1 > stream_ptr_after_chunk)
                            break;
                        pixel_skip = bytestream2_get_byte(&g2);
                        pixel_ptr += pixel_skip;
                        pixel_countdown -= pixel_skip;
                        byte_run = sign_extend(bytestream2_get_byte(&g2),8);
                        if (byte_run > 0) {
                            CHECK_PIXEL_PTR(byte_run);
                            if (bytestream2_tell(&g2) + byte_run > stream_ptr_after_chunk)
                                break;
                            for (j = 0; j < byte_run; j++, pixel_countdown--) {
                                pixels[pixel_ptr++] = bytestream2_get_byte(&g2);
                            }
                        } else if (byte_run < 0) {
                            byte_run = -byte_run;
                            palette_idx1 = bytestream2_get_byte(&g2);
                            CHECK_PIXEL_PTR(byte_run);
                            for (j = 0; j < byte_run; j++, pixel_countdown--) {
                                pixels[pixel_ptr++] = palette_idx1;
                            }
                        }
                    }
                }

                y_ptr += s->frame->linesize[0];
                compressed_lines--;
            }
            break;

        case FLI_BLACK:
            /* set the whole frame to color 0 (which is usually black) */
            memset(pixels, 0,
                s->frame->linesize[0] * s->avctx->height);
            break;

        case FLI_BRUN:
            /* Byte run compression: This chunk type only occurs in the first
             * FLI frame and it will update the entire frame. */
            y_ptr = 0;
            for (lines = 0; lines < s->avctx->height; lines++) {
                pixel_ptr = y_ptr;
                /* disregard the line packets; instead, iterate through all
                 * pixels on a row */
                 bytestream2_skip(&g2, 1);
                pixel_countdown = s->avctx->width;
                while (pixel_countdown > 0) {
                    if (bytestream2_tell(&g2) + 1 > stream_ptr_after_chunk)
                        break;
                    byte_run = sign_extend(bytestream2_get_byte(&g2), 8);
                    if (!byte_run) {
                        av_log(avctx, AV_LOG_ERROR, "Invalid byte run value.\n");
                        return AVERROR_INVALIDDATA;
                    }

                    if (byte_run > 0) {
                        palette_idx1 = bytestream2_get_byte(&g2);
                        CHECK_PIXEL_PTR(byte_run);
                        for (j = 0; j < byte_run; j++) {
                            pixels[pixel_ptr++] = palette_idx1;
                            pixel_countdown--;
                            if (pixel_countdown < 0)
                                av_log(avctx, AV_LOG_ERROR, "pixel_countdown < 0 (%d) at line %d\n",
                                       pixel_countdown, lines);
                        }
                    } else {  /* copy bytes if byte_run < 0 */
                        byte_run = -byte_run;
                        CHECK_PIXEL_PTR(byte_run);
                        if (bytestream2_tell(&g2) + byte_run > stream_ptr_after_chunk)
                            break;
                        for (j = 0; j < byte_run; j++) {
                            pixels[pixel_ptr++] = bytestream2_get_byte(&g2);
                            pixel_countdown--;
                            if (pixel_countdown < 0)
                                av_log(avctx, AV_LOG_ERROR, "pixel_countdown < 0 (%d) at line %d\n",
                                       pixel_countdown, lines);
                        }
                    }
                }

                y_ptr += s->frame->linesize[0];
            }
            break;

        case FLI_COPY:
            /* copy the chunk (uncompressed frame) */
            if (chunk_size - 6 != FFALIGN(s->avctx->width, 4) * s->avctx->height) {
                av_log(avctx, AV_LOG_ERROR, "In chunk FLI_COPY : source data (%d bytes) " \
                       "has incorrect size, skipping chunk\n", chunk_size - 6);
                bytestream2_skip(&g2, chunk_size - 6);
            } else {
                for (y_ptr = 0; y_ptr < s->frame->linesize[0] * s->avctx->height;
                     y_ptr += s->frame->linesize[0]) {
                    bytestream2_get_buffer(&g2, &pixels[y_ptr],
                                           s->avctx->width);
                    if (s->avctx->width & 3)
                        bytestream2_skip(&g2, 4 - (s->avctx->width & 3));
                }
            }
            break;

        case FLI_MINI:
            /* some sort of a thumbnail? disregard this chunk... */
            break;

        default:
            av_log(avctx, AV_LOG_ERROR, "Unrecognized chunk type: %d\n", chunk_type);
            break;
        }

        if (stream_ptr_after_chunk - bytestream2_tell(&g2) >= 0) {
            bytestream2_skip(&g2, stream_ptr_after_chunk - bytestream2_tell(&g2));
        } else {
            av_log(avctx, AV_LOG_ERROR, "Chunk overread\n");
            break;
        }

        frame_size -= chunk_size;
        num_chunks--;
    }

    /* by the end of the chunk, the stream ptr should equal the frame
     * size (minus 1 or 2, possibly); if it doesn't, issue a warning */
    if (bytestream2_get_bytes_left(&g2) > 2)
        av_log(avctx, AV_LOG_ERROR, "Processed FLI chunk where chunk size = %d " \
               "and final chunk ptr = %d\n", buf_size,
               buf_size - bytestream2_get_bytes_left(&g2));

    /* make the palette available on the way out */
    memcpy(s->frame->data[1], s->palette, AVPALETTE_SIZE);
    if (s->new_palette) {
        s->frame->palette_has_changed = 1;
        s->new_palette = 0;
    }

    if ((ret = av_frame_ref(data, s->frame)) < 0)
        return ret;

    *got_frame = 1;

    return buf_size;
}