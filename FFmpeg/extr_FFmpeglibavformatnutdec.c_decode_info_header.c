#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  type_str ;
typedef  int /*<<< orphan*/  str_value ;
typedef  int /*<<< orphan*/  name ;
typedef  size_t int64_t ;
struct TYPE_16__ {int /*<<< orphan*/ * metadata; } ;
struct TYPE_15__ {size_t nb_streams; int event_flags; int /*<<< orphan*/ * metadata; TYPE_3__** streams; int /*<<< orphan*/ * pb; } ;
struct TYPE_12__ {long long num; long long den; } ;
struct TYPE_14__ {int event_flags; TYPE_1__ r_frame_rate; int /*<<< orphan*/ * metadata; } ;
struct TYPE_13__ {size_t time_base_count; int /*<<< orphan*/ * time_base; TYPE_4__* avf; } ;
typedef  TYPE_2__ NUTContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_5__ AVChapter ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVFMT_EVENT_FLAG_METADATA_UPDATED ; 
 int AVSTREAM_EVENT_FLAG_METADATA_UPDATED ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_V (unsigned int,int) ; 
 int /*<<< orphan*/  INFO_STARTCODE ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ av_strcasecmp (char*,char*) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 TYPE_5__* avpriv_new_chapter (TYPE_4__*,int,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ ffio_get_checksum (int /*<<< orphan*/ *) ; 
 void* ffio_read_varlen (int /*<<< orphan*/ *) ; 
 size_t get_packetheader (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* get_s (int /*<<< orphan*/ *) ; 
 int get_str (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  set_disposition_bits (TYPE_4__*,char*,unsigned int) ; 
 scalar_t__ skip_reserved (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sscanf (char*,char*,long long*,long long*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int decode_info_header(NUTContext *nut)
{
    AVFormatContext *s = nut->avf;
    AVIOContext *bc    = s->pb;
    uint64_t tmp, chapter_start, chapter_len;
    unsigned int stream_id_plus1, count;
    int chapter_id, i, ret = 0;
    int64_t value, end;
    char name[256], str_value[1024], type_str[256];
    const char *type;
    int *event_flags        = NULL;
    AVChapter *chapter      = NULL;
    AVStream *st            = NULL;
    AVDictionary **metadata = NULL;
    int metadata_flag       = 0;

    end  = get_packetheader(nut, bc, 1, INFO_STARTCODE);
    end += avio_tell(bc);

    GET_V(stream_id_plus1, tmp <= s->nb_streams);
    chapter_id    = get_s(bc);
    chapter_start = ffio_read_varlen(bc);
    chapter_len   = ffio_read_varlen(bc);
    count         = ffio_read_varlen(bc);

    if (chapter_id && !stream_id_plus1) {
        int64_t start = chapter_start / nut->time_base_count;
        chapter = avpriv_new_chapter(s, chapter_id,
                                     nut->time_base[chapter_start %
                                                    nut->time_base_count],
                                     start, start + chapter_len, NULL);
        if (!chapter) {
            av_log(s, AV_LOG_ERROR, "Could not create chapter.\n");
            return AVERROR(ENOMEM);
        }
        metadata = &chapter->metadata;
    } else if (stream_id_plus1) {
        st       = s->streams[stream_id_plus1 - 1];
        metadata = &st->metadata;
        event_flags = &st->event_flags;
        metadata_flag = AVSTREAM_EVENT_FLAG_METADATA_UPDATED;
    } else {
        metadata = &s->metadata;
        event_flags = &s->event_flags;
        metadata_flag = AVFMT_EVENT_FLAG_METADATA_UPDATED;
    }

    for (i = 0; i < count; i++) {
        ret = get_str(bc, name, sizeof(name));
        if (ret < 0) {
            av_log(s, AV_LOG_ERROR, "get_str failed while decoding info header\n");
            return ret;
        }
        value = get_s(bc);
        str_value[0] = 0;

        if (value == -1) {
            type = "UTF-8";
            ret = get_str(bc, str_value, sizeof(str_value));
        } else if (value == -2) {
            ret = get_str(bc, type_str, sizeof(type_str));
            if (ret < 0) {
                av_log(s, AV_LOG_ERROR, "get_str failed while decoding info header\n");
                return ret;
            }
            type = type_str;
            ret = get_str(bc, str_value, sizeof(str_value));
        } else if (value == -3) {
            type  = "s";
            value = get_s(bc);
        } else if (value == -4) {
            type  = "t";
            value = ffio_read_varlen(bc);
        } else if (value < -4) {
            type = "r";
            get_s(bc);
        } else {
            type = "v";
        }

        if (ret < 0) {
            av_log(s, AV_LOG_ERROR, "get_str failed while decoding info header\n");
            return ret;
        }

        if (stream_id_plus1 > s->nb_streams) {
            av_log(s, AV_LOG_WARNING,
                   "invalid stream id %d for info packet\n",
                   stream_id_plus1);
            continue;
        }

        if (!strcmp(type, "UTF-8")) {
            if (chapter_id == 0 && !strcmp(name, "Disposition")) {
                set_disposition_bits(s, str_value, stream_id_plus1 - 1);
                continue;
            }

            if (stream_id_plus1 && !strcmp(name, "r_frame_rate")) {
                sscanf(str_value, "%d/%d", &st->r_frame_rate.num, &st->r_frame_rate.den);
                if (st->r_frame_rate.num >= 1000LL*st->r_frame_rate.den ||
                    st->r_frame_rate.num < 0 || st->r_frame_rate.den < 0)
                    st->r_frame_rate.num = st->r_frame_rate.den = 0;
                continue;
            }

            if (metadata && av_strcasecmp(name, "Uses") &&
                av_strcasecmp(name, "Depends") && av_strcasecmp(name, "Replaces")) {
                if (event_flags)
                    *event_flags |= metadata_flag;
                av_dict_set(metadata, name, str_value, 0);
            }
        }
    }

    if (skip_reserved(bc, end) || ffio_get_checksum(bc)) {
        av_log(s, AV_LOG_ERROR, "info header checksum mismatch\n");
        return AVERROR_INVALIDDATA;
    }
fail:
    return FFMIN(ret, 0);
}