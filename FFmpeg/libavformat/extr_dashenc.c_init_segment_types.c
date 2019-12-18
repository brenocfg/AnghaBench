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
struct TYPE_12__ {int nb_streams; TYPE_2__** streams; TYPE_4__* priv_data; } ;
struct TYPE_11__ {scalar_t__ hls_playlist; int /*<<< orphan*/  single_file; int /*<<< orphan*/  segment_type_option; TYPE_3__* streams; } ;
struct TYPE_10__ {int /*<<< orphan*/  extension_name; int /*<<< orphan*/  format_name; scalar_t__ segment_type; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {int /*<<< orphan*/  codec_id; } ;
typedef  scalar_t__ SegmentType ;
typedef  TYPE_3__ OutputStream ;
typedef  TYPE_4__ DASHContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_MUXER_NOT_FOUND ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ SEGMENT_TYPE_MP4 ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_extension_str (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_format_str (scalar_t__) ; 
 scalar_t__ select_segment_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_segment_types(AVFormatContext *s)
{
    DASHContext *c = s->priv_data;
    int has_mp4_streams = 0;
    for (int i = 0; i < s->nb_streams; ++i) {
        OutputStream *os = &c->streams[i];
        SegmentType segment_type = select_segment_type(
            c->segment_type_option, s->streams[i]->codecpar->codec_id);
        os->segment_type = segment_type;
        os->format_name = get_format_str(segment_type);
        if (!os->format_name) {
            av_log(s, AV_LOG_ERROR, "Could not select DASH segment type for stream %d\n", i);
            return AVERROR_MUXER_NOT_FOUND;
        }
        os->extension_name = get_extension_str(segment_type, c->single_file);
        if (!os->extension_name) {
            av_log(s, AV_LOG_ERROR, "Could not get extension type for stream %d\n", i);
            return AVERROR_MUXER_NOT_FOUND;
        }

        has_mp4_streams |= segment_type == SEGMENT_TYPE_MP4;
    }

    if (c->hls_playlist && !has_mp4_streams) {
         av_log(s, AV_LOG_WARNING, "No mp4 streams, disabling HLS manifest generation\n");
         c->hls_playlist = 0;
    }

    return 0;
}