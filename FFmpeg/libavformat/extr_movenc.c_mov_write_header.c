#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  value; } ;
struct TYPE_29__ {int nb_streams; TYPE_5__** streams; scalar_t__ nb_chapters; int /*<<< orphan*/  metadata; TYPE_4__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_28__ {int /*<<< orphan*/  metadata; TYPE_1__* codecpar; } ;
struct TYPE_27__ {int mode; int flags; scalar_t__ reserved_moov_size; int moov_written; void* reserved_header_pos; scalar_t__ nb_meta_tmcd; scalar_t__ chapter_track; scalar_t__ time; int /*<<< orphan*/  max_fragment_size; int /*<<< orphan*/  max_fragment_duration; TYPE_3__* tracks; } ;
struct TYPE_26__ {scalar_t__ tag; scalar_t__ language; int /*<<< orphan*/  multichannel_as_mono; TYPE_2__* par; scalar_t__ vos_len; scalar_t__ vos_data; } ;
struct TYPE_25__ {scalar_t__ channel_layout; } ;
struct TYPE_24__ {scalar_t__ codec_id; scalar_t__ codec_type; int /*<<< orphan*/  extradata; scalar_t__ extradata_size; } ;
typedef  TYPE_3__ MOVTrack ;
typedef  TYPE_4__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVTimecode ;
typedef  TYPE_5__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;
typedef  TYPE_7__ AVDictionaryEntry ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CH_LAYOUT_MONO ; 
 scalar_t__ AV_CODEC_ID_DNXHD ; 
 scalar_t__ AV_CODEC_ID_DVD_SUBTITLE ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_MOV_FLAG_DELAY_MOOV ; 
 int FF_MOV_FLAG_EMPTY_MOOV ; 
 int FF_MOV_FLAG_FASTSTART ; 
 int FF_MOV_FLAG_FRAGMENT ; 
 int FF_MOV_FLAG_FRAG_CUSTOM ; 
 int FF_MOV_FLAG_FRAG_EVERY_FRAME ; 
 int FF_MOV_FLAG_FRAG_KEYFRAME ; 
 int FF_MOV_FLAG_GLOBAL_SIDX ; 
 int FF_MOV_FLAG_ISML ; 
 int FF_MOV_FLAG_RTP_HINT ; 
 int MODE_IPOD ; 
 int MODE_MOV ; 
 int MODE_MP4 ; 
 int /*<<< orphan*/  TAG_IS_AVCI (scalar_t__) ; 
 TYPE_7__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,scalar_t__) ; 
 void* avio_tell (int /*<<< orphan*/ *) ; 
 int ff_mov_init_hinting (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  ff_parse_creation_time_metadata (TYPE_6__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mov_check_timecode_track (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mov_create_chapter_track (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  mov_create_dvd_sub_decoder_specific_info (TYPE_3__*,TYPE_5__*) ; 
 int mov_create_timecode_track (TYPE_6__*,int,int,int /*<<< orphan*/ ) ; 
 int mov_write_identification (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  mov_write_isml_manifest (int /*<<< orphan*/ *,TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  mov_write_mdat_tag (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int mov_write_moov_tag (int /*<<< orphan*/ *,TYPE_4__*,TYPE_6__*) ; 
 scalar_t__ rtp_hinting_needed (TYPE_5__*) ; 

__attribute__((used)) static int mov_write_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    MOVMuxContext *mov = s->priv_data;
    AVDictionaryEntry *t, *global_tcr = av_dict_get(s->metadata, "timecode", NULL, 0);
    int i, ret, hint_track = 0, tmcd_track = 0, nb_tracks = s->nb_streams;

    if (mov->mode & (MODE_MP4|MODE_MOV|MODE_IPOD) && s->nb_chapters)
        nb_tracks++;

    if (mov->flags & FF_MOV_FLAG_RTP_HINT) {
        hint_track = nb_tracks;
        for (i = 0; i < s->nb_streams; i++)
            if (rtp_hinting_needed(s->streams[i]))
                nb_tracks++;
    }

    if (mov->nb_meta_tmcd)
        tmcd_track = nb_tracks;

    for (i = 0; i < s->nb_streams; i++) {
        int j;
        AVStream *st= s->streams[i];
        MOVTrack *track= &mov->tracks[i];

        /* copy extradata if it exists */
        if (st->codecpar->extradata_size) {
            if (st->codecpar->codec_id == AV_CODEC_ID_DVD_SUBTITLE)
                mov_create_dvd_sub_decoder_specific_info(track, st);
            else if (!TAG_IS_AVCI(track->tag) && st->codecpar->codec_id != AV_CODEC_ID_DNXHD) {
                track->vos_len  = st->codecpar->extradata_size;
                track->vos_data = av_malloc(track->vos_len + AV_INPUT_BUFFER_PADDING_SIZE);
                if (!track->vos_data) {
                    return AVERROR(ENOMEM);
                }
                memcpy(track->vos_data, st->codecpar->extradata, track->vos_len);
                memset(track->vos_data + track->vos_len, 0, AV_INPUT_BUFFER_PADDING_SIZE);
            }
        }

        if (st->codecpar->codec_type != AVMEDIA_TYPE_AUDIO ||
            track->par->channel_layout != AV_CH_LAYOUT_MONO)
            continue;

        for (j = 0; j < s->nb_streams; j++) {
            AVStream *stj= s->streams[j];
            MOVTrack *trackj= &mov->tracks[j];
            if (j == i)
                continue;

            if (stj->codecpar->codec_type != AVMEDIA_TYPE_AUDIO ||
                trackj->par->channel_layout != AV_CH_LAYOUT_MONO ||
                trackj->language != track->language ||
                trackj->tag != track->tag
            )
                continue;
            track->multichannel_as_mono++;
        }
    }

    if (!(mov->flags & FF_MOV_FLAG_DELAY_MOOV)) {
        if ((ret = mov_write_identification(pb, s)) < 0)
            return ret;
    }

    if (mov->reserved_moov_size){
        mov->reserved_header_pos = avio_tell(pb);
        if (mov->reserved_moov_size > 0)
            avio_skip(pb, mov->reserved_moov_size);
    }

    if (mov->flags & FF_MOV_FLAG_FRAGMENT) {
        /* If no fragmentation options have been set, set a default. */
        if (!(mov->flags & (FF_MOV_FLAG_FRAG_KEYFRAME |
                            FF_MOV_FLAG_FRAG_CUSTOM |
                            FF_MOV_FLAG_FRAG_EVERY_FRAME)) &&
            !mov->max_fragment_duration && !mov->max_fragment_size)
            mov->flags |= FF_MOV_FLAG_FRAG_KEYFRAME;
    } else {
        if (mov->flags & FF_MOV_FLAG_FASTSTART)
            mov->reserved_header_pos = avio_tell(pb);
        mov_write_mdat_tag(pb, mov);
    }

    ff_parse_creation_time_metadata(s, &mov->time, 1);
    if (mov->time)
        mov->time += 0x7C25B080; // 1970 based -> 1904 based

    if (mov->chapter_track)
        if ((ret = mov_create_chapter_track(s, mov->chapter_track)) < 0)
            return ret;

    if (mov->flags & FF_MOV_FLAG_RTP_HINT) {
        for (i = 0; i < s->nb_streams; i++) {
            if (rtp_hinting_needed(s->streams[i])) {
                if ((ret = ff_mov_init_hinting(s, hint_track, i)) < 0)
                    return ret;
                hint_track++;
            }
        }
    }

    if (mov->nb_meta_tmcd) {
        /* Initialize the tmcd tracks */
        for (i = 0; i < s->nb_streams; i++) {
            AVStream *st = s->streams[i];
            t = global_tcr;

            if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                AVTimecode tc;
                if (!t)
                    t = av_dict_get(st->metadata, "timecode", NULL, 0);
                if (!t)
                    continue;
                if (mov_check_timecode_track(s, &tc, i, t->value) < 0)
                    continue;
                if ((ret = mov_create_timecode_track(s, tmcd_track, i, tc)) < 0)
                    return ret;
                tmcd_track++;
            }
        }
    }

    avio_flush(pb);

    if (mov->flags & FF_MOV_FLAG_ISML)
        mov_write_isml_manifest(pb, mov, s);

    if (mov->flags & FF_MOV_FLAG_EMPTY_MOOV &&
        !(mov->flags & FF_MOV_FLAG_DELAY_MOOV)) {
        if ((ret = mov_write_moov_tag(pb, mov, s)) < 0)
            return ret;
        avio_flush(pb);
        mov->moov_written = 1;
        if (mov->flags & FF_MOV_FLAG_GLOBAL_SIDX)
            mov->reserved_header_pos = avio_tell(pb);
    }

    return 0;
}