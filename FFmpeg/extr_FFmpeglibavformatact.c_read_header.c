#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int sample_rate; int frame_size; int channels; int /*<<< orphan*/  codec_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  bytes_left_in_chunk; } ;
struct TYPE_12__ {int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_11__ {TYPE_6__* codecpar; int /*<<< orphan*/  duration; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ACTContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_CODEC_ID_G729 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CHUNK_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  av_rescale (int,int,int) ; 
 TYPE_1__* avformat_new_stream (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  ff_get_wav_header (TYPE_2__*,int /*<<< orphan*/ *,TYPE_6__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_header(AVFormatContext *s)
{
    ACTContext* ctx = s->priv_data;
    AVIOContext *pb = s->pb;
    int size;
    AVStream* st;

    int min,sec,msec;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    avio_skip(pb, 16);
    size=avio_rl32(pb);
    ff_get_wav_header(s, pb, st->codecpar, size, 0);

    /*
      8000Hz (Fine-rec) file format has 10 bytes long
      packets with 10ms of sound data in them
    */
    if (st->codecpar->sample_rate != 8000) {
        av_log(s, AV_LOG_ERROR, "Sample rate %d is not supported.\n", st->codecpar->sample_rate);
        return AVERROR_INVALIDDATA;
    }

    st->codecpar->frame_size=80;
    st->codecpar->channels=1;
    avpriv_set_pts_info(st, 64, 1, 100);

    st->codecpar->codec_id=AV_CODEC_ID_G729;

    avio_seek(pb, 257, SEEK_SET);
    msec=avio_rl16(pb);
    sec=avio_r8(pb);
    min=avio_rl32(pb);

    st->duration = av_rescale(1000*(min*60+sec)+msec, st->codecpar->sample_rate, 1000 * st->codecpar->frame_size);

    ctx->bytes_left_in_chunk=CHUNK_SIZE;

    avio_seek(pb, 512, SEEK_SET);

    return 0;
}