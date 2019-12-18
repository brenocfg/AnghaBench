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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int blocksize; int samples; int flags; int crc; scalar_t__ final; scalar_t__ initial; } ;
typedef  TYPE_1__ WvHeader ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int WV_HEADER_SIZE ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int ff_wv_parse_header (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int mkv_strip_wavpack(const uint8_t *src, uint8_t **pdst, int *size)
{
    uint8_t *dst;
    int srclen = *size;
    int offset = 0;
    int ret;

    dst = av_malloc(srclen);
    if (!dst)
        return AVERROR(ENOMEM);

    while (srclen >= WV_HEADER_SIZE) {
        WvHeader header;

        ret = ff_wv_parse_header(&header, src);
        if (ret < 0)
            goto fail;
        src    += WV_HEADER_SIZE;
        srclen -= WV_HEADER_SIZE;

        if (srclen < header.blocksize) {
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }

        if (header.initial) {
            AV_WL32(dst + offset, header.samples);
            offset += 4;
        }
        AV_WL32(dst + offset,     header.flags);
        AV_WL32(dst + offset + 4, header.crc);
        offset += 8;

        if (!(header.initial && header.final)) {
            AV_WL32(dst + offset, header.blocksize);
            offset += 4;
        }

        memcpy(dst + offset, src, header.blocksize);
        src    += header.blocksize;
        srclen -= header.blocksize;
        offset += header.blocksize;
    }

    *pdst = dst;
    *size = offset;

    return 0;
fail:
    av_freep(&dst);
    return ret;
}