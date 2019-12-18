#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int int64_t ;
struct TYPE_12__ {scalar_t__ codec_id; char* extradata; int channels; } ;
struct TYPE_11__ {TYPE_1__** streams; int /*<<< orphan*/ * pb; } ;
struct TYPE_10__ {TYPE_6__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int ALAC_HEADER ; 
 int ALAC_NEW_KUKI ; 
 int ALAC_PREAMBLE ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 scalar_t__ AV_CODEC_ID_ALAC ; 
 scalar_t__ AV_CODEC_ID_OPUS ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_WB32 (char*,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int avio_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_2__*,char*) ; 
 scalar_t__ ff_alloc_extradata (TYPE_6__*,int) ; 
 scalar_t__ ff_get_extradata (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_mov_read_esds (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int read_kuki_chunk(AVFormatContext *s, int64_t size)
{
    AVIOContext *pb = s->pb;
    AVStream *st      = s->streams[0];

    if (size < 0 || size > INT_MAX - AV_INPUT_BUFFER_PADDING_SIZE)
        return -1;

    if (st->codecpar->codec_id == AV_CODEC_ID_AAC) {
        /* The magic cookie format for AAC is an mp4 esds atom.
           The lavc AAC decoder requires the data from the codec specific
           description as extradata input. */
        int strt, skip;

        strt = avio_tell(pb);
        ff_mov_read_esds(s, pb);
        skip = size - (avio_tell(pb) - strt);
        if (skip < 0 || !st->codecpar->extradata ||
            st->codecpar->codec_id != AV_CODEC_ID_AAC) {
            av_log(s, AV_LOG_ERROR, "invalid AAC magic cookie\n");
            return AVERROR_INVALIDDATA;
        }
        avio_skip(pb, skip);
    } else if (st->codecpar->codec_id == AV_CODEC_ID_ALAC) {
#define ALAC_PREAMBLE 12
#define ALAC_HEADER   36
#define ALAC_NEW_KUKI 24
        uint8_t preamble[12];
        if (size < ALAC_NEW_KUKI) {
            av_log(s, AV_LOG_ERROR, "invalid ALAC magic cookie\n");
            avio_skip(pb, size);
            return AVERROR_INVALIDDATA;
        }
        if (avio_read(pb, preamble, ALAC_PREAMBLE) != ALAC_PREAMBLE) {
            av_log(s, AV_LOG_ERROR, "failed to read preamble\n");
            return AVERROR_INVALIDDATA;
        }

        av_freep(&st->codecpar->extradata);
        if (ff_alloc_extradata(st->codecpar, ALAC_HEADER))
            return AVERROR(ENOMEM);

        /* For the old style cookie, we skip 12 bytes, then read 36 bytes.
         * The new style cookie only contains the last 24 bytes of what was
         * 36 bytes in the old style cookie, so we fabricate the first 12 bytes
         * in that case to maintain compatibility. */
        if (!memcmp(&preamble[4], "frmaalac", 8)) {
            if (size < ALAC_PREAMBLE + ALAC_HEADER) {
                av_log(s, AV_LOG_ERROR, "invalid ALAC magic cookie\n");
                av_freep(&st->codecpar->extradata);
                return AVERROR_INVALIDDATA;
            }
            if (avio_read(pb, st->codecpar->extradata, ALAC_HEADER) != ALAC_HEADER) {
                av_log(s, AV_LOG_ERROR, "failed to read kuki header\n");
                av_freep(&st->codecpar->extradata);
                return AVERROR_INVALIDDATA;
            }
            avio_skip(pb, size - ALAC_PREAMBLE - ALAC_HEADER);
        } else {
            AV_WB32(st->codecpar->extradata, 36);
            memcpy(&st->codecpar->extradata[4], "alac", 4);
            AV_WB32(&st->codecpar->extradata[8], 0);
            memcpy(&st->codecpar->extradata[12], preamble, 12);
            if (avio_read(pb, &st->codecpar->extradata[24], ALAC_NEW_KUKI - 12) != ALAC_NEW_KUKI - 12) {
                av_log(s, AV_LOG_ERROR, "failed to read new kuki header\n");
                av_freep(&st->codecpar->extradata);
                return AVERROR_INVALIDDATA;
            }
            avio_skip(pb, size - ALAC_NEW_KUKI);
        }
    } else if (st->codecpar->codec_id == AV_CODEC_ID_OPUS) {
        // The data layout for Opus is currently unknown, so we do not export
        // extradata at all. Multichannel streams are not supported.
        if (st->codecpar->channels > 2) {
            avpriv_request_sample(s, "multichannel Opus in CAF");
            return AVERROR_PATCHWELCOME;
        }
        avio_skip(pb, size);
    } else {
        av_freep(&st->codecpar->extradata);
        if (ff_get_extradata(s, st->codecpar, pb, size) < 0)
            return AVERROR(ENOMEM);
    }

    return 0;
}