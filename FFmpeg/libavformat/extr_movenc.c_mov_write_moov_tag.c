#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_22__ {int nb_streams; int /*<<< orphan*/ ** streams; } ;
struct TYPE_21__ {int nb_streams; int flags; int chapter_track; scalar_t__ mode; TYPE_2__* tracks; int /*<<< orphan*/  iods_skip; int /*<<< orphan*/  time; } ;
struct TYPE_20__ {scalar_t__ entry; scalar_t__ tref_tag; scalar_t__ tag; size_t src_track; int /*<<< orphan*/  timescale; int /*<<< orphan*/  track_duration; int /*<<< orphan*/  track_id; int /*<<< orphan*/  tref_id; int /*<<< orphan*/  st; TYPE_1__* par; int /*<<< orphan*/  time; } ;
struct TYPE_19__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  TYPE_3__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_PKT_DATA_FALLBACK_TRACK ; 
 int FF_MOV_FLAG_FRAGMENT ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 scalar_t__ MODE_MOV ; 
 scalar_t__ MODE_PSP ; 
 int /*<<< orphan*/  av_rescale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ av_stream_get_side_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_chunks (TYPE_2__*) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_setup_track_ids (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mov_write_iods_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_mvex_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_mvhd_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int mov_write_trak_tag (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_udta_tag (int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mov_write_uuidusmt_tag (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_moov_tag(AVIOContext *pb, MOVMuxContext *mov,
                              AVFormatContext *s)
{
    int i;
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0); /* size placeholder*/
    ffio_wfourcc(pb, "moov");

    mov_setup_track_ids(mov, s);

    for (i = 0; i < mov->nb_streams; i++) {
        if (mov->tracks[i].entry <= 0 && !(mov->flags & FF_MOV_FLAG_FRAGMENT))
            continue;

        mov->tracks[i].time     = mov->time;

        if (mov->tracks[i].entry)
            build_chunks(&mov->tracks[i]);
    }

    if (mov->chapter_track)
        for (i = 0; i < s->nb_streams; i++) {
            mov->tracks[i].tref_tag = MKTAG('c','h','a','p');
            mov->tracks[i].tref_id  = mov->tracks[mov->chapter_track].track_id;
        }
    for (i = 0; i < mov->nb_streams; i++) {
        MOVTrack *track = &mov->tracks[i];
        if (track->tag == MKTAG('r','t','p',' ')) {
            track->tref_tag = MKTAG('h','i','n','t');
            track->tref_id = mov->tracks[track->src_track].track_id;
        } else if (track->par->codec_type == AVMEDIA_TYPE_AUDIO) {
            int * fallback, size;
            fallback = (int*)av_stream_get_side_data(track->st,
                                                     AV_PKT_DATA_FALLBACK_TRACK,
                                                     &size);
            if (fallback != NULL && size == sizeof(int)) {
                if (*fallback >= 0 && *fallback < mov->nb_streams) {
                    track->tref_tag = MKTAG('f','a','l','l');
                    track->tref_id = mov->tracks[*fallback].track_id;
                }
            }
        }
    }
    for (i = 0; i < mov->nb_streams; i++) {
        if (mov->tracks[i].tag == MKTAG('t','m','c','d')) {
            int src_trk = mov->tracks[i].src_track;
            mov->tracks[src_trk].tref_tag = mov->tracks[i].tag;
            mov->tracks[src_trk].tref_id  = mov->tracks[i].track_id;
            //src_trk may have a different timescale than the tmcd track
            mov->tracks[i].track_duration = av_rescale(mov->tracks[src_trk].track_duration,
                                                       mov->tracks[i].timescale,
                                                       mov->tracks[src_trk].timescale);
        }
    }

    mov_write_mvhd_tag(pb, mov);
    if (mov->mode != MODE_MOV && !mov->iods_skip)
        mov_write_iods_tag(pb, mov);
    for (i = 0; i < mov->nb_streams; i++) {
        if (mov->tracks[i].entry > 0 || mov->flags & FF_MOV_FLAG_FRAGMENT) {
            int ret = mov_write_trak_tag(s, pb, mov, &(mov->tracks[i]), i < s->nb_streams ? s->streams[i] : NULL);
            if (ret < 0)
                return ret;
        }
    }
    if (mov->flags & FF_MOV_FLAG_FRAGMENT)
        mov_write_mvex_tag(pb, mov); /* QuickTime requires trak to precede this */

    if (mov->mode == MODE_PSP)
        mov_write_uuidusmt_tag(pb, s);
    else
        mov_write_udta_tag(pb, mov, s);

    return update_size(pb, pos);
}