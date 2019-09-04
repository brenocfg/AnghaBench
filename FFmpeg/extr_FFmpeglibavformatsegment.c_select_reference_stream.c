#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_11__ {int disposition; TYPE_1__* codecpar; } ;
struct TYPE_10__ {int nb_streams; TYPE_6__** streams; TYPE_2__* priv_data; } ;
struct TYPE_9__ {int reference_stream_index; int /*<<< orphan*/  reference_stream_specifier; } ;
struct TYPE_8__ {int codec_type; } ;
typedef  TYPE_2__ SegmentContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AVMEDIA_TYPE_ATTACHMENT 132 
#define  AVMEDIA_TYPE_AUDIO 131 
#define  AVMEDIA_TYPE_DATA 130 
 int AVMEDIA_TYPE_NB ; 
#define  AVMEDIA_TYPE_SUBTITLE 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int AV_DISPOSITION_ATTACHED_PIC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_ARRAY_ELEMS (int const*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int avformat_match_stream_specifier (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int select_reference_stream(AVFormatContext *s)
{
    SegmentContext *seg = s->priv_data;
    int ret, i;

    seg->reference_stream_index = -1;
    if (!strcmp(seg->reference_stream_specifier, "auto")) {
        /* select first index of type with highest priority */
        int type_index_map[AVMEDIA_TYPE_NB];
        static const enum AVMediaType type_priority_list[] = {
            AVMEDIA_TYPE_VIDEO,
            AVMEDIA_TYPE_AUDIO,
            AVMEDIA_TYPE_SUBTITLE,
            AVMEDIA_TYPE_DATA,
            AVMEDIA_TYPE_ATTACHMENT
        };
        enum AVMediaType type;

        for (i = 0; i < AVMEDIA_TYPE_NB; i++)
            type_index_map[i] = -1;

        /* select first index for each type */
        for (i = 0; i < s->nb_streams; i++) {
            type = s->streams[i]->codecpar->codec_type;
            if ((unsigned)type < AVMEDIA_TYPE_NB && type_index_map[type] == -1
                /* ignore attached pictures/cover art streams */
                && !(s->streams[i]->disposition & AV_DISPOSITION_ATTACHED_PIC))
                type_index_map[type] = i;
        }

        for (i = 0; i < FF_ARRAY_ELEMS(type_priority_list); i++) {
            type = type_priority_list[i];
            if ((seg->reference_stream_index = type_index_map[type]) >= 0)
                break;
        }
    } else {
        for (i = 0; i < s->nb_streams; i++) {
            ret = avformat_match_stream_specifier(s, s->streams[i],
                                                  seg->reference_stream_specifier);
            if (ret < 0)
                return ret;
            if (ret > 0) {
                seg->reference_stream_index = i;
                break;
            }
        }
    }

    if (seg->reference_stream_index < 0) {
        av_log(s, AV_LOG_ERROR, "Could not select stream matching identifier '%s'\n",
               seg->reference_stream_specifier);
        return AVERROR(EINVAL);
    }

    return 0;
}