#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int nb_streams; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_12__ {TYPE_1__* codecpar; } ;
struct TYPE_11__ {scalar_t__ mode; } ;
struct TYPE_10__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ MOVMuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MODE_PSP ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_cover_image (TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_ftyp_tag (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int mov_write_uuidprof_tag (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static int mov_write_identification(AVIOContext *pb, AVFormatContext *s)
{
    MOVMuxContext *mov = s->priv_data;
    int i;

    mov_write_ftyp_tag(pb,s);
    if (mov->mode == MODE_PSP) {
        int video_streams_nb = 0, audio_streams_nb = 0, other_streams_nb = 0;
        for (i = 0; i < s->nb_streams; i++) {
            AVStream *st = s->streams[i];
            if (is_cover_image(st))
                continue;
            if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
                video_streams_nb++;
            else if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
                audio_streams_nb++;
            else
                other_streams_nb++;
            }

        if (video_streams_nb != 1 || audio_streams_nb != 1 || other_streams_nb) {
            av_log(s, AV_LOG_ERROR, "PSP mode need one video and one audio stream\n");
            return AVERROR(EINVAL);
        }
        return mov_write_uuidprof_tag(pb, s);
    }
    return 0;
}