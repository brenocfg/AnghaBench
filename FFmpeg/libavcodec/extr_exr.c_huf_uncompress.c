#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ int32_t ;
typedef  TYPE_1__ HufDec ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HUF_DECSIZE ; 
 scalar_t__ HUF_ENCSIZE ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 TYPE_1__* av_mallocz_array (int,int) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int huf_build_dec_table (TYPE_1__*,scalar_t__,scalar_t__,TYPE_1__*) ; 
 int huf_decode (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int huf_unpack_enc_table (int /*<<< orphan*/ *,scalar_t__,scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static int huf_uncompress(GetByteContext *gb,
                          uint16_t *dst, int dst_size)
{
    int32_t src_size, im, iM;
    uint32_t nBits;
    uint64_t *freq;
    HufDec *hdec;
    int ret, i;

    src_size = bytestream2_get_le32(gb);
    im       = bytestream2_get_le32(gb);
    iM       = bytestream2_get_le32(gb);
    bytestream2_skip(gb, 4);
    nBits = bytestream2_get_le32(gb);
    if (im < 0 || im >= HUF_ENCSIZE ||
        iM < 0 || iM >= HUF_ENCSIZE ||
        src_size < 0)
        return AVERROR_INVALIDDATA;

    bytestream2_skip(gb, 4);

    freq = av_mallocz_array(HUF_ENCSIZE, sizeof(*freq));
    hdec = av_mallocz_array(HUF_DECSIZE, sizeof(*hdec));
    if (!freq || !hdec) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    if ((ret = huf_unpack_enc_table(gb, im, iM, freq)) < 0)
        goto fail;

    if (nBits > 8 * bytestream2_get_bytes_left(gb)) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    if ((ret = huf_build_dec_table(freq, im, iM, hdec)) < 0)
        goto fail;
    ret = huf_decode(freq, hdec, gb, nBits, iM, dst_size, dst);

fail:
    for (i = 0; i < HUF_DECSIZE; i++)
        if (hdec)
            av_freep(&hdec[i].p);

    av_free(freq);
    av_free(hdec);

    return ret;
}