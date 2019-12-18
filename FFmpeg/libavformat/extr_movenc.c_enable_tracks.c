#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int nb_streams; TYPE_4__** streams; TYPE_3__* priv_data; } ;
struct TYPE_11__ {int disposition; TYPE_1__* codecpar; } ;
struct TYPE_10__ {int per_stream_grouping; TYPE_2__* tracks; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int codec_type; } ;
typedef  TYPE_3__ MOVMuxContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 130 
 int AVMEDIA_TYPE_NB ; 
#define  AVMEDIA_TYPE_SUBTITLE 129 
 int AVMEDIA_TYPE_UNKNOWN ; 
#define  AVMEDIA_TYPE_VIDEO 128 
 int AV_DISPOSITION_DEFAULT ; 
 int /*<<< orphan*/  MOV_TRACK_ENABLED ; 
 scalar_t__ is_cover_image (TYPE_4__*) ; 

__attribute__((used)) static void enable_tracks(AVFormatContext *s)
{
    MOVMuxContext *mov = s->priv_data;
    int i;
    int enabled[AVMEDIA_TYPE_NB];
    int first[AVMEDIA_TYPE_NB];

    for (i = 0; i < AVMEDIA_TYPE_NB; i++) {
        enabled[i] = 0;
        first[i] = -1;
    }

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];

        if (st->codecpar->codec_type <= AVMEDIA_TYPE_UNKNOWN ||
            st->codecpar->codec_type >= AVMEDIA_TYPE_NB ||
            is_cover_image(st))
            continue;

        if (first[st->codecpar->codec_type] < 0)
            first[st->codecpar->codec_type] = i;
        if (st->disposition & AV_DISPOSITION_DEFAULT) {
            mov->tracks[i].flags |= MOV_TRACK_ENABLED;
            enabled[st->codecpar->codec_type]++;
        }
    }

    for (i = 0; i < AVMEDIA_TYPE_NB; i++) {
        switch (i) {
        case AVMEDIA_TYPE_VIDEO:
        case AVMEDIA_TYPE_AUDIO:
        case AVMEDIA_TYPE_SUBTITLE:
            if (enabled[i] > 1)
                mov->per_stream_grouping = 1;
            if (!enabled[i] && first[i] >= 0)
                mov->tracks[first[i]].flags |= MOV_TRACK_ENABLED;
            break;
        }
    }
}