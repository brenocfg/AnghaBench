#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_23__ {int seekable; } ;
struct TYPE_22__ {int channels; int bits_per_coded_sample; int* extradata; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_21__ {TYPE_8__* pb; int /*<<< orphan*/  metadata; TYPE_1__* priv_data; } ;
struct TYPE_20__ {int duration; scalar_t__ start_time; TYPE_7__* codecpar; } ;
struct TYPE_19__ {int ver; int fcount; int lastframe; int curbits; int /*<<< orphan*/  frames; scalar_t__ frames_noted; scalar_t__ curframe; } ;
typedef  int /*<<< orphan*/  MPCFrame ;
typedef  TYPE_1__ MPCContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CODEC_ID_MUSEPACK7 ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MKTAG (char,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPC_FRAMESIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_malloc (int) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avio_r8 (TYPE_8__*) ; 
 scalar_t__ avio_rl24 (TYPE_8__*) ; 
 int avio_rl32 (TYPE_8__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int avio_tell (TYPE_8__*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_ape_parse_tag (TYPE_3__*) ; 
 scalar_t__ ff_get_extradata (TYPE_3__*,TYPE_7__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  ff_id3v1_read (TYPE_3__*) ; 
 int /*<<< orphan*/ * mpc_rate ; 

__attribute__((used)) static int mpc_read_header(AVFormatContext *s)
{
    MPCContext *c = s->priv_data;
    AVStream *st;

    if(avio_rl24(s->pb) != MKTAG('M', 'P', '+', 0)){
        av_log(s, AV_LOG_ERROR, "Not a Musepack file\n");
        return AVERROR_INVALIDDATA;
    }
    c->ver = avio_r8(s->pb);
    if(c->ver != 0x07 && c->ver != 0x17){
        av_log(s, AV_LOG_ERROR, "Can demux Musepack SV7, got version %02X\n", c->ver);
        return AVERROR_INVALIDDATA;
    }
    c->fcount = avio_rl32(s->pb);
    if((int64_t)c->fcount * sizeof(MPCFrame) >= UINT_MAX){
        av_log(s, AV_LOG_ERROR, "Too many frames, seeking is not possible\n");
        return AVERROR_INVALIDDATA;
    }
    if(c->fcount){
        c->frames = av_malloc(c->fcount * sizeof(MPCFrame));
        if(!c->frames){
            av_log(s, AV_LOG_ERROR, "Cannot allocate seektable\n");
            return AVERROR(ENOMEM);
        }
    }else{
        av_log(s, AV_LOG_WARNING, "Container reports no frames\n");
    }
    c->curframe = 0;
    c->lastframe = -1;
    c->curbits = 8;
    c->frames_noted = 0;

    st = avformat_new_stream(s, NULL);
    if (!st)
        goto mem_error;
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id = AV_CODEC_ID_MUSEPACK7;
    st->codecpar->channels = 2;
    st->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;
    st->codecpar->bits_per_coded_sample = 16;

    if (ff_get_extradata(s, st->codecpar, s->pb, 16) < 0)
        goto mem_error;
    st->codecpar->sample_rate = mpc_rate[st->codecpar->extradata[2] & 3];
    avpriv_set_pts_info(st, 32, MPC_FRAMESIZE, st->codecpar->sample_rate);
    /* scan for seekpoints */
    st->start_time = 0;
    st->duration = c->fcount;

    /* try to read APE tags */
    if (s->pb->seekable & AVIO_SEEKABLE_NORMAL) {
        int64_t pos = avio_tell(s->pb);
        ff_ape_parse_tag(s);
        if (!av_dict_get(s->metadata, "", NULL, AV_DICT_IGNORE_SUFFIX))
            ff_id3v1_read(s);
        avio_seek(s->pb, pos, SEEK_SET);
    }

    return 0;
mem_error:
    av_freep(&c->frames);
    return AVERROR(ENOMEM);
}