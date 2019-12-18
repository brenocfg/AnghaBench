#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ buffer; } ;
struct TYPE_8__ {scalar_t__ avail_in; unsigned char* next_in; scalar_t__ avail_out; int /*<<< orphan*/  next_out; } ;
struct TYPE_7__ {int pic_state; scalar_t__ crow_size; TYPE_4__ zstream; int /*<<< orphan*/  avctx; int /*<<< orphan*/  crow_buf; TYPE_5__ gb; } ;
typedef  TYPE_1__ PNGDecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ FFMIN (int,int /*<<< orphan*/ ) ; 
 int PNG_ALLIMAGE ; 
 int Z_OK ; 
 int /*<<< orphan*/  Z_PARTIAL_FLUSH ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bytestream2_get_bytes_left (TYPE_5__*) ; 
 int /*<<< orphan*/  bytestream2_skip (TYPE_5__*,int) ; 
 int inflate (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_handle_row (TYPE_1__*) ; 

__attribute__((used)) static int png_decode_idat(PNGDecContext *s, int length)
{
    int ret;
    s->zstream.avail_in = FFMIN(length, bytestream2_get_bytes_left(&s->gb));
    s->zstream.next_in  = (unsigned char *)s->gb.buffer;
    bytestream2_skip(&s->gb, length);

    /* decode one line if possible */
    while (s->zstream.avail_in > 0) {
        ret = inflate(&s->zstream, Z_PARTIAL_FLUSH);
        if (ret != Z_OK && ret != Z_STREAM_END) {
            av_log(s->avctx, AV_LOG_ERROR, "inflate returned error %d\n", ret);
            return AVERROR_EXTERNAL;
        }
        if (s->zstream.avail_out == 0) {
            if (!(s->pic_state & PNG_ALLIMAGE)) {
                png_handle_row(s);
            }
            s->zstream.avail_out = s->crow_size;
            s->zstream.next_out  = s->crow_buf;
        }
        if (ret == Z_STREAM_END && s->zstream.avail_in > 0) {
            av_log(s->avctx, AV_LOG_WARNING,
                   "%d undecompressed bytes left in buffer\n", s->zstream.avail_in);
            return 0;
        }
    }
    return 0;
}