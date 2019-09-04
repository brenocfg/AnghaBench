#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int int64_t ;
struct TYPE_19__ {int seekable; } ;
struct TYPE_18__ {scalar_t__ probesize; TYPE_8__* pb; int /*<<< orphan*/  metadata; TYPE_2__* iformat; } ;
struct TYPE_17__ {int /*<<< orphan*/  need_parsing; TYPE_1__* codecpar; } ;
struct TYPE_16__ {int /*<<< orphan*/  raw_codec_id; } ;
struct TYPE_15__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL_RAW ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_feof (TYPE_8__*) ; 
 int avio_r8 (TYPE_8__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (TYPE_8__*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  ff_ape_parse_tag (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_id3v1_read (TYPE_4__*) ; 

__attribute__((used)) static int adts_aac_read_header(AVFormatContext *s)
{
    AVStream *st;
    uint16_t state;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id   = s->iformat->raw_codec_id;
    st->need_parsing         = AVSTREAM_PARSE_FULL_RAW;

    ff_id3v1_read(s);
    if ((s->pb->seekable & AVIO_SEEKABLE_NORMAL) &&
        !av_dict_get(s->metadata, "", NULL, AV_DICT_IGNORE_SUFFIX)) {
        int64_t cur = avio_tell(s->pb);
        ff_ape_parse_tag(s);
        avio_seek(s->pb, cur, SEEK_SET);
    }

    // skip data until the first ADTS frame is found
    state = avio_r8(s->pb);
    while (!avio_feof(s->pb) && avio_tell(s->pb) < s->probesize) {
        state = (state << 8) | avio_r8(s->pb);
        if ((state >> 4) != 0xFFF)
            continue;
        avio_seek(s->pb, -2, SEEK_CUR);
        break;
    }
    if ((state >> 4) != 0xFFF)
        return AVERROR_INVALIDDATA;

    // LCM of all possible ADTS sample rates
    avpriv_set_pts_info(st, 64, 1, 28224000);

    return 0;
}