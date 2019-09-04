#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_15__ {char* url; TYPE_2__** streams; int /*<<< orphan*/  pb; int /*<<< orphan*/  nb_streams; TYPE_4__* priv_data; } ;
struct TYPE_11__ {TYPE_3__* elem; } ;
struct TYPE_14__ {scalar_t__ bandwidth; int /*<<< orphan*/  is_live; TYPE_1__ tracks; int /*<<< orphan*/  duration; } ;
struct TYPE_13__ {scalar_t__ num; } ;
struct TYPE_12__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_3__ MatroskaTrack ;
typedef  TYPE_4__ MatroskaDemuxContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  BANDWIDTH ; 
 int /*<<< orphan*/  DURATION ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FILENAME ; 
 int /*<<< orphan*/  INITIALIZATION_RANGE ; 
 int /*<<< orphan*/  TRACK_NUMBER ; 
 char* av_asprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matroska_read_close (TYPE_5__*) ; 
 int matroska_read_header (TYPE_5__*) ; 
 char* strrchr (char*,char) ; 
 int webm_dash_manifest_cues (TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static int webm_dash_manifest_read_header(AVFormatContext *s)
{
    char *buf;
    int ret = matroska_read_header(s);
    int64_t init_range;
    MatroskaTrack *tracks;
    MatroskaDemuxContext *matroska = s->priv_data;
    if (ret) {
        av_log(s, AV_LOG_ERROR, "Failed to read file headers\n");
        return -1;
    }
    if (!s->nb_streams) {
        matroska_read_close(s);
        av_log(s, AV_LOG_ERROR, "No streams found\n");
        return AVERROR_INVALIDDATA;
    }

    if (!matroska->is_live) {
        buf = av_asprintf("%g", matroska->duration);
        if (!buf) return AVERROR(ENOMEM);
        av_dict_set(&s->streams[0]->metadata, DURATION, buf, 0);
        av_free(buf);

        // initialization range
        // 5 is the offset of Cluster ID.
        init_range = avio_tell(s->pb) - 5;
        av_dict_set_int(&s->streams[0]->metadata, INITIALIZATION_RANGE, init_range, 0);
    }

    // basename of the file
    buf = strrchr(s->url, '/');
    av_dict_set(&s->streams[0]->metadata, FILENAME, buf ? ++buf : s->url, 0);

    // track number
    tracks = matroska->tracks.elem;
    av_dict_set_int(&s->streams[0]->metadata, TRACK_NUMBER, tracks[0].num, 0);

    // parse the cues and populate Cue related fields
    if (!matroska->is_live) {
        ret = webm_dash_manifest_cues(s, init_range);
        if (ret < 0) {
            av_log(s, AV_LOG_ERROR, "Error parsing Cues\n");
            return ret;
        }
    }

    // use the bandwidth from the command line if it was provided
    if (matroska->bandwidth > 0) {
        av_dict_set_int(&s->streams[0]->metadata, BANDWIDTH,
                        matroska->bandwidth, 0);
    }
    return 0;
}