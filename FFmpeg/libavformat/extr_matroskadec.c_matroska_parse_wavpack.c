#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {TYPE_2__* stream; } ;
struct TYPE_6__ {TYPE_1__* codecpar; } ;
struct TYPE_5__ {int extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  TYPE_3__ MatroskaTrack ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_RL16 (int /*<<< orphan*/ ) ; 
 int AV_RL32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WL16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_realloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int matroska_parse_wavpack(MatroskaTrack *track, uint8_t *src,
                                  uint8_t **pdst, int *size)
{
    uint8_t *dst = NULL;
    int dstlen   = 0;
    int srclen   = *size;
    uint32_t samples;
    uint16_t ver;
    int ret, offset = 0;

    if (srclen < 12 || track->stream->codecpar->extradata_size < 2)
        return AVERROR_INVALIDDATA;

    ver = AV_RL16(track->stream->codecpar->extradata);

    samples = AV_RL32(src);
    src    += 4;
    srclen -= 4;

    while (srclen >= 8) {
        int multiblock;
        uint32_t blocksize;
        uint8_t *tmp;

        uint32_t flags = AV_RL32(src);
        uint32_t crc   = AV_RL32(src + 4);
        src    += 8;
        srclen -= 8;

        multiblock = (flags & 0x1800) != 0x1800;
        if (multiblock) {
            if (srclen < 4) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            blocksize = AV_RL32(src);
            src      += 4;
            srclen   -= 4;
        } else
            blocksize = srclen;

        if (blocksize > srclen) {
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }

        tmp = av_realloc(dst, dstlen + blocksize + 32 + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!tmp) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        dst     = tmp;
        dstlen += blocksize + 32;

        AV_WL32(dst + offset, MKTAG('w', 'v', 'p', 'k'));   // tag
        AV_WL32(dst + offset +  4, blocksize + 24);         // blocksize - 8
        AV_WL16(dst + offset +  8, ver);                    // version
        AV_WL16(dst + offset + 10, 0);                      // track/index_no
        AV_WL32(dst + offset + 12, 0);                      // total samples
        AV_WL32(dst + offset + 16, 0);                      // block index
        AV_WL32(dst + offset + 20, samples);                // number of samples
        AV_WL32(dst + offset + 24, flags);                  // flags
        AV_WL32(dst + offset + 28, crc);                    // crc
        memcpy(dst + offset + 32, src, blocksize);          // block data

        src    += blocksize;
        srclen -= blocksize;
        offset += blocksize + 32;
    }

    memset(dst + dstlen, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    *pdst = dst;
    *size = dstlen;

    return 0;

fail:
    av_freep(&dst);
    return ret;
}