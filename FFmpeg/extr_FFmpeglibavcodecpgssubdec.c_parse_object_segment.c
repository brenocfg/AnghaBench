#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {scalar_t__ count; TYPE_1__* object; } ;
struct TYPE_10__ {unsigned int width; unsigned int height; TYPE_2__* priv_data; } ;
struct TYPE_9__ {TYPE_6__ objects; } ;
struct TYPE_8__ {int id; int rle_remaining_len; int rle_data_len; unsigned int w; unsigned int h; scalar_t__ rle; int /*<<< orphan*/  rle_buffer_size; } ;
typedef  TYPE_1__ PGSSubObject ;
typedef  TYPE_2__ PGSSubContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MAX_EPOCH_OBJECTS ; 
 int /*<<< orphan*/  av_fast_padded_malloc (scalar_t__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 void* bytestream_get_be16 (int const**) ; 
 int bytestream_get_be24 (int const**) ; 
 int bytestream_get_byte (int const**) ; 
 TYPE_1__* find_object (int,TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int const*,int) ; 

__attribute__((used)) static int parse_object_segment(AVCodecContext *avctx,
                                  const uint8_t *buf, int buf_size)
{
    PGSSubContext *ctx = avctx->priv_data;
    PGSSubObject *object;

    uint8_t sequence_desc;
    unsigned int rle_bitmap_len, width, height;
    int id;

    if (buf_size <= 4)
        return AVERROR_INVALIDDATA;
    buf_size -= 4;

    id = bytestream_get_be16(&buf);
    object = find_object(id, &ctx->objects);
    if (!object) {
        if (ctx->objects.count >= MAX_EPOCH_OBJECTS) {
            av_log(avctx, AV_LOG_ERROR, "Too many objects in epoch\n");
            return AVERROR_INVALIDDATA;
        }
        object = &ctx->objects.object[ctx->objects.count++];
        object->id = id;
    }

    /* skip object version number */
    buf += 1;

    /* Read the Sequence Description to determine if start of RLE data or appended to previous RLE */
    sequence_desc = bytestream_get_byte(&buf);

    if (!(sequence_desc & 0x80)) {
        /* Additional RLE data */
        if (buf_size > object->rle_remaining_len)
            return AVERROR_INVALIDDATA;

        memcpy(object->rle + object->rle_data_len, buf, buf_size);
        object->rle_data_len += buf_size;
        object->rle_remaining_len -= buf_size;

        return 0;
    }

    if (buf_size <= 7)
        return AVERROR_INVALIDDATA;
    buf_size -= 7;

    /* Decode rle bitmap length, stored size includes width/height data */
    rle_bitmap_len = bytestream_get_be24(&buf) - 2*2;

    if (buf_size > rle_bitmap_len) {
        av_log(avctx, AV_LOG_ERROR,
               "Buffer dimension %d larger than the expected RLE data %d\n",
               buf_size, rle_bitmap_len);
        return AVERROR_INVALIDDATA;
    }

    /* Get bitmap dimensions from data */
    width  = bytestream_get_be16(&buf);
    height = bytestream_get_be16(&buf);

    /* Make sure the bitmap is not too large */
    if (avctx->width < width || avctx->height < height || !width || !height) {
        av_log(avctx, AV_LOG_ERROR, "Bitmap dimensions (%dx%d) invalid.\n", width, height);
        return AVERROR_INVALIDDATA;
    }

    object->w = width;
    object->h = height;

    av_fast_padded_malloc(&object->rle, &object->rle_buffer_size, rle_bitmap_len);

    if (!object->rle) {
        object->rle_data_len = 0;
        object->rle_remaining_len = 0;
        return AVERROR(ENOMEM);
    }

    memcpy(object->rle, buf, buf_size);
    object->rle_data_len = buf_size;
    object->rle_remaining_len = rle_bitmap_len - buf_size;

    return 0;
}