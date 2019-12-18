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
struct TYPE_6__ {scalar_t__ extradata_size; int /*<<< orphan*/  extradata; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** header; scalar_t__* header_len; } ;
typedef  TYPE_1__ OGGStreamContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ SPEEX_HEADER_SIZE ; 
 int /*<<< orphan*/ * av_mallocz (scalar_t__) ; 
 int /*<<< orphan*/  bytestream_put_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * ogg_write_vorbiscomment (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ogg_build_speex_headers(AVCodecParameters *par,
                                   OGGStreamContext *oggstream, int bitexact,
                                   AVDictionary **m)
{
    uint8_t *p;

    if (par->extradata_size < SPEEX_HEADER_SIZE)
        return AVERROR_INVALIDDATA;

    // first packet: Speex header
    p = av_mallocz(SPEEX_HEADER_SIZE);
    if (!p)
        return AVERROR(ENOMEM);
    oggstream->header[0] = p;
    oggstream->header_len[0] = SPEEX_HEADER_SIZE;
    bytestream_put_buffer(&p, par->extradata, SPEEX_HEADER_SIZE);
    AV_WL32(&oggstream->header[0][68], 0);  // set extra_headers to 0

    // second packet: VorbisComment
    p = ogg_write_vorbiscomment(0, bitexact, &oggstream->header_len[1], m, 0, NULL, 0);
    if (!p)
        return AVERROR(ENOMEM);
    oggstream->header[1] = p;

    return 0;
}