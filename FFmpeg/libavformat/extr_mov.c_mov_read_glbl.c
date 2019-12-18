#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_15__ {int extradata_size; unsigned int codec_tag; int /*<<< orphan*/  codec_id; scalar_t__ extradata; } ;
struct TYPE_14__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_13__ {TYPE_9__* codecpar; } ;
struct TYPE_12__ {int size; unsigned int type; } ;
struct TYPE_11__ {TYPE_8__* fc; } ;
typedef  TYPE_1__ MOVContext ;
typedef  TYPE_2__ MOVAtom ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_CODEC_ID_HEVC ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 unsigned int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 unsigned int avio_rb32 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ff_get_extradata (TYPE_8__*,TYPE_9__*,int /*<<< orphan*/ *,unsigned int) ; 
 int mov_read_default (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__) ; 

__attribute__((used)) static int mov_read_glbl(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    int ret;

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];

    if ((uint64_t)atom.size > (1<<30))
        return AVERROR_INVALIDDATA;

    if (atom.size >= 10) {
        // Broken files created by legacy versions of libavformat will
        // wrap a whole fiel atom inside of a glbl atom.
        unsigned size = avio_rb32(pb);
        unsigned type = avio_rl32(pb);
        avio_seek(pb, -8, SEEK_CUR);
        if (type == MKTAG('f','i','e','l') && size == atom.size)
            return mov_read_default(c, pb, atom);
    }
    if (st->codecpar->extradata_size > 1 && st->codecpar->extradata) {
        av_log(c->fc, AV_LOG_WARNING, "ignoring multiple glbl\n");
        return 0;
    }
    av_freep(&st->codecpar->extradata);
    ret = ff_get_extradata(c->fc, st->codecpar, pb, atom.size);
    if (ret < 0)
        return ret;
    if (atom.type == MKTAG('h','v','c','C') && st->codecpar->codec_tag == MKTAG('d','v','h','1'))
        /* HEVC-based Dolby Vision derived from hvc1.
           Happens to match with an identifier
           previously utilized for DV. Thus, if we have
           the hvcC extradata box available as specified,
           set codec to HEVC */
        st->codecpar->codec_id = AV_CODEC_ID_HEVC;

    return 0;
}