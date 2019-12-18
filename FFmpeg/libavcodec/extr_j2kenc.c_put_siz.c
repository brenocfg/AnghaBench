#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int buf_end; int buf; int ncomponents; int* chroma_shift; int /*<<< orphan*/  tile_height; int /*<<< orphan*/  tile_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ Jpeg2000EncoderContext ;

/* Variables and functions */
 int JPEG2000_SIZ ; 
 int /*<<< orphan*/  bytestream_put_be16 (int*,int) ; 
 int /*<<< orphan*/  bytestream_put_be32 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_byte (int*,int) ; 

__attribute__((used)) static int put_siz(Jpeg2000EncoderContext *s)
{
    int i;

    if (s->buf_end - s->buf < 40 + 3 * s->ncomponents)
        return -1;

    bytestream_put_be16(&s->buf, JPEG2000_SIZ);
    bytestream_put_be16(&s->buf, 38 + 3 * s->ncomponents); // Lsiz
    bytestream_put_be16(&s->buf, 0); // Rsiz
    bytestream_put_be32(&s->buf, s->width); // width
    bytestream_put_be32(&s->buf, s->height); // height
    bytestream_put_be32(&s->buf, 0); // X0Siz
    bytestream_put_be32(&s->buf, 0); // Y0Siz

    bytestream_put_be32(&s->buf, s->tile_width); // XTSiz
    bytestream_put_be32(&s->buf, s->tile_height); // YTSiz
    bytestream_put_be32(&s->buf, 0); // XT0Siz
    bytestream_put_be32(&s->buf, 0); // YT0Siz
    bytestream_put_be16(&s->buf, s->ncomponents); // CSiz

    for (i = 0; i < s->ncomponents; i++){ // Ssiz_i XRsiz_i, YRsiz_i
        bytestream_put_byte(&s->buf, 7);
        bytestream_put_byte(&s->buf, i?1<<s->chroma_shift[0]:1);
        bytestream_put_byte(&s->buf, i?1<<s->chroma_shift[1]:1);
    }
    return 0;
}