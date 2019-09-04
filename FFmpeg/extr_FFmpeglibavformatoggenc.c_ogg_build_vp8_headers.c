#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_15__ {TYPE_1__ sample_aspect_ratio; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_12__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_11__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_14__ {int /*<<< orphan*/  metadata; TYPE_3__ time_base; TYPE_2__ r_frame_rate; TYPE_6__* codecpar; } ;
struct TYPE_13__ {int isvp8; int /*<<< orphan*/ ** header; int /*<<< orphan*/ * header_len; } ;
typedef  TYPE_4__ OGGStreamContext ;
typedef  TYPE_5__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_6__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  VP8_HEADER_SIZE ; 
 scalar_t__ av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * av_mallocz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_5__*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bytestream_put_be16 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_be24 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_be32 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_buffer (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  bytestream_put_byte (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * ogg_write_vorbiscomment (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ogg_build_vp8_headers(AVFormatContext *s, AVStream *st,
                                 OGGStreamContext *oggstream, int bitexact)
{
    AVCodecParameters *par = st->codecpar;
    uint8_t *p;

    /* first packet: VP8 header */
    p = av_mallocz(VP8_HEADER_SIZE);
    if (!p)
        return AVERROR(ENOMEM);
    oggstream->header[0] = p;
    oggstream->header_len[0] = VP8_HEADER_SIZE;
    bytestream_put_byte(&p, 0x4f); // HDRID
    bytestream_put_buffer(&p, "VP80", 4); // Identifier
    bytestream_put_byte(&p, 1); // HDRTYP
    bytestream_put_byte(&p, 1); // VMAJ
    bytestream_put_byte(&p, 0); // VMIN
    bytestream_put_be16(&p, par->width);
    bytestream_put_be16(&p, par->height);
    bytestream_put_be24(&p, par->sample_aspect_ratio.num);
    bytestream_put_be24(&p, par->sample_aspect_ratio.den);
    if (st->r_frame_rate.num > 0 && st->r_frame_rate.den > 0) {
        // OggVP8 requires pts to increase by 1 per visible frame, so use the least common
        // multiple framerate if available.
        av_log(s, AV_LOG_DEBUG, "Changing time base from %d/%d to %d/%d\n",
               st->time_base.num, st->time_base.den,
               st->r_frame_rate.den, st->r_frame_rate.num);
        avpriv_set_pts_info(st, 64, st->r_frame_rate.den, st->r_frame_rate.num);
    }
    bytestream_put_be32(&p, st->time_base.den);
    bytestream_put_be32(&p, st->time_base.num);

    /* optional second packet: VorbisComment */
    if (av_dict_get(st->metadata, "", NULL, AV_DICT_IGNORE_SUFFIX)) {
        p = ogg_write_vorbiscomment(7, bitexact, &oggstream->header_len[1], &st->metadata, 0, NULL, 0);
        if (!p)
            return AVERROR(ENOMEM);
        oggstream->header[1] = p;
        bytestream_put_byte(&p, 0x4f); // HDRID
        bytestream_put_buffer(&p, "VP80", 4); // Identifier
        bytestream_put_byte(&p, 2); // HDRTYP
        bytestream_put_byte(&p, 0x20);
    }

    oggstream->isvp8 = 1;

    return 0;
}