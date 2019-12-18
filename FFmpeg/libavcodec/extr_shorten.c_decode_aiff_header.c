#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int bits_per_coded_sample; int sample_rate; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int swap; } ;
typedef  TYPE_1__ ShortenContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  ENOSYS ; 
 scalar_t__ MKTAG (char,char,float,char) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_be32 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_be64 (int /*<<< orphan*/ *) ; 
 long long bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_aiff_header(AVCodecContext *avctx, const uint8_t *header,
                              int header_size)
{
    ShortenContext *s = avctx->priv_data;
    int len, bps, exp;
    GetByteContext gb;
    uint64_t val;
    uint32_t tag;

    bytestream2_init(&gb, header, header_size);

    if (bytestream2_get_le32(&gb) != MKTAG('F', 'O', 'R', 'M')) {
        av_log(avctx, AV_LOG_ERROR, "missing FORM tag\n");
        return AVERROR_INVALIDDATA;
    }

    bytestream2_skip(&gb, 4); /* chunk size */

    tag = bytestream2_get_le32(&gb);
    if (tag != MKTAG('A', 'I', 'F', 'F') &&
        tag != MKTAG('A', 'I', 'F', 'C')) {
        av_log(avctx, AV_LOG_ERROR, "missing AIFF tag\n");
        return AVERROR_INVALIDDATA;
    }

    while (bytestream2_get_le32(&gb) != MKTAG('C', 'O', 'M', 'M')) {
        len = bytestream2_get_be32(&gb);
        if (len < 0 || bytestream2_get_bytes_left(&gb) < 18LL + len + (len&1)) {
            av_log(avctx, AV_LOG_ERROR, "no COMM chunk found\n");
            return AVERROR_INVALIDDATA;
        }
        bytestream2_skip(&gb, len + (len & 1));
    }
    len = bytestream2_get_be32(&gb);

    if (len < 18) {
        av_log(avctx, AV_LOG_ERROR, "COMM chunk was too short\n");
        return AVERROR_INVALIDDATA;
    }

    bytestream2_skip(&gb, 6);
    bps = bytestream2_get_be16(&gb);
    avctx->bits_per_coded_sample = bps;

    s->swap = tag == MKTAG('A', 'I', 'F', 'C');

    if (bps != 16 && bps != 8) {
        av_log(avctx, AV_LOG_ERROR, "unsupported number of bits per sample: %d\n", bps);
        return AVERROR(ENOSYS);
    }

    exp = bytestream2_get_be16(&gb) - 16383 - 63;
    val = bytestream2_get_be64(&gb);
    if (exp < -63 || exp > 63) {
        av_log(avctx, AV_LOG_ERROR, "exp %d is out of range\n", exp);
        return AVERROR_INVALIDDATA;
    }
    if (exp >= 0)
        avctx->sample_rate = val << exp;
    else
        avctx->sample_rate = (val + (1ULL<<(-exp-1))) >> -exp;
    len -= 18;
    if (len > 0)
        av_log(avctx, AV_LOG_INFO, "%d header bytes unparsed\n", len);

    return 0;
}