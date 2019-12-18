#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_25__ {unsigned int den; } ;
struct TYPE_24__ {unsigned int id; scalar_t__ duration; TYPE_1__* priv_data; int /*<<< orphan*/  time_base; } ;
struct TYPE_23__ {scalar_t__ size; } ;
struct TYPE_17__ {unsigned int nb_items; int complete; TYPE_3__* item; } ;
struct TYPE_22__ {TYPE_12__ frag_index; TYPE_13__* fc; } ;
struct TYPE_21__ {unsigned int nb_stream_info; TYPE_2__* stream_info; } ;
struct TYPE_20__ {scalar_t__ sidx_pts; } ;
struct TYPE_19__ {int has_sidx; int /*<<< orphan*/  time_scale; scalar_t__ track_end; } ;
struct TYPE_18__ {unsigned int nb_streams; TYPE_6__** streams; } ;
typedef  TYPE_1__ MOVStreamContext ;
typedef  TYPE_2__ MOVFragmentStreamInfo ;
typedef  TYPE_3__ MOVFragmentIndexItem ;
typedef  TYPE_4__ MOVContext ;
typedef  TYPE_5__ MOVAtom ;
typedef  TYPE_6__ AVStream ;
typedef  TYPE_7__ AVRational ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_log (TYPE_13__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 TYPE_7__ av_make_q (int,void*) ; 
 scalar_t__ av_rescale (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ av_rescale_q (scalar_t__,TYPE_7__,int /*<<< orphan*/ ) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb24 (int /*<<< orphan*/ *) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rb64 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_size (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_13__*,char*,...) ; 
 TYPE_2__* get_frag_stream_info (TYPE_12__*,int,unsigned int) ; 
 int update_frag_index (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int mov_read_sidx(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    int64_t offset = avio_tell(pb) + atom.size, pts, timestamp;
    uint8_t version;
    unsigned i, j, track_id, item_count;
    AVStream *st = NULL;
    AVStream *ref_st = NULL;
    MOVStreamContext *sc, *ref_sc = NULL;
    AVRational timescale;

    version = avio_r8(pb);
    if (version > 1) {
        avpriv_request_sample(c->fc, "sidx version %u", version);
        return 0;
    }

    avio_rb24(pb); // flags

    track_id = avio_rb32(pb); // Reference ID
    for (i = 0; i < c->fc->nb_streams; i++) {
        if (c->fc->streams[i]->id == track_id) {
            st = c->fc->streams[i];
            break;
        }
    }
    if (!st) {
        av_log(c->fc, AV_LOG_WARNING, "could not find corresponding track id %d\n", track_id);
        return 0;
    }

    sc = st->priv_data;

    timescale = av_make_q(1, avio_rb32(pb));

    if (timescale.den <= 0) {
        av_log(c->fc, AV_LOG_ERROR, "Invalid sidx timescale 1/%d\n", timescale.den);
        return AVERROR_INVALIDDATA;
    }

    if (version == 0) {
        pts = avio_rb32(pb);
        offset += avio_rb32(pb);
    } else {
        pts = avio_rb64(pb);
        offset += avio_rb64(pb);
    }

    avio_rb16(pb); // reserved

    item_count = avio_rb16(pb);

    for (i = 0; i < item_count; i++) {
        int index;
        MOVFragmentStreamInfo * frag_stream_info;
        uint32_t size = avio_rb32(pb);
        uint32_t duration = avio_rb32(pb);
        if (size & 0x80000000) {
            avpriv_request_sample(c->fc, "sidx reference_type 1");
            return AVERROR_PATCHWELCOME;
        }
        avio_rb32(pb); // sap_flags
        timestamp = av_rescale_q(pts, timescale, st->time_base);

        index = update_frag_index(c, offset);
        frag_stream_info = get_frag_stream_info(&c->frag_index, index, track_id);
        if (frag_stream_info)
            frag_stream_info->sidx_pts = timestamp;

        offset += size;
        pts += duration;
    }

    st->duration = sc->track_end = pts;

    sc->has_sidx = 1;

    if (offset == avio_size(pb)) {
        // Find first entry in fragment index that came from an sidx.
        // This will pretty much always be the first entry.
        for (i = 0; i < c->frag_index.nb_items; i++) {
            MOVFragmentIndexItem * item = &c->frag_index.item[i];
            for (j = 0; ref_st == NULL && j < item->nb_stream_info; j++) {
                MOVFragmentStreamInfo * si;
                si = &item->stream_info[j];
                if (si->sidx_pts != AV_NOPTS_VALUE) {
                    ref_st = c->fc->streams[j];
                    ref_sc = ref_st->priv_data;
                    break;
                }
            }
        }
        if (ref_st) for (i = 0; i < c->fc->nb_streams; i++) {
            st = c->fc->streams[i];
            sc = st->priv_data;
            if (!sc->has_sidx) {
                st->duration = sc->track_end = av_rescale(ref_st->duration, sc->time_scale, ref_sc->time_scale);
            }
        }

        c->frag_index.complete = 1;
    }

    return 0;
}