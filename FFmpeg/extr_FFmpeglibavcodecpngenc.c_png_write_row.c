#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int avail_in; scalar_t__ avail_out; int /*<<< orphan*/  next_out; int /*<<< orphan*/  const* next_in; } ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {scalar_t__ bytestream_end; scalar_t__ bytestream; int /*<<< orphan*/  buf; TYPE_5__ zstream; } ;
typedef  TYPE_1__ PNGEncContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ IOBUF_SIZE ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int deflate (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_image_data (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int png_write_row(AVCodecContext *avctx, const uint8_t *data, int size)
{
    PNGEncContext *s = avctx->priv_data;
    int ret;

    s->zstream.avail_in = size;
    s->zstream.next_in  = data;
    while (s->zstream.avail_in > 0) {
        ret = deflate(&s->zstream, Z_NO_FLUSH);
        if (ret != Z_OK)
            return -1;
        if (s->zstream.avail_out == 0) {
            if (s->bytestream_end - s->bytestream > IOBUF_SIZE + 100)
                png_write_image_data(avctx, s->buf, IOBUF_SIZE);
            s->zstream.avail_out = IOBUF_SIZE;
            s->zstream.next_out  = s->buf;
        }
    }
    return 0;
}