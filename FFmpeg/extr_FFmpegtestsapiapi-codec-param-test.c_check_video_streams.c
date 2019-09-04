#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_14__ {scalar_t__ codec_type; } ;
struct TYPE_13__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_12__ {scalar_t__ type; char* name; } ;
struct TYPE_11__ {TYPE_4__* codec; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVOption ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_OPT_TYPE_CONST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 scalar_t__ av_opt_get (TYPE_4__*,char*,int /*<<< orphan*/ ,char**) ; 
 TYPE_2__* av_opt_next (TYPE_4__*,TYPE_2__ const*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int check_video_streams(const AVFormatContext *fmt_ctx1, const AVFormatContext *fmt_ctx2)
{
    int i;
    int ret = 0;

    av_assert0(fmt_ctx1->nb_streams == fmt_ctx2->nb_streams);
    for (i = 0; i < fmt_ctx1->nb_streams; i++) {
        const AVOption *opt = NULL;
        const AVStream *st1 = fmt_ctx1->streams[i];
        const AVStream *st2 = fmt_ctx2->streams[i];
        AVCodecContext *codec_ctx1 = st1->codec;
        AVCodecContext *codec_ctx2 = st2->codec;

        if (codec_ctx1->codec_type != AVMEDIA_TYPE_VIDEO)
            continue;

        while (opt = av_opt_next(codec_ctx1, opt)) {
            uint8_t *str1 = NULL, *str2 = NULL;

            if (opt->type == AV_OPT_TYPE_CONST)
                continue;

            if (!strcmp(opt->name, "frame_number"))
                continue;

            av_assert0(av_opt_get(codec_ctx1, opt->name, 0, &str1) >= 0);
            av_assert0(av_opt_get(codec_ctx2, opt->name, 0, &str2) >= 0);
            if (strcmp(str1, str2)) {
                av_log(NULL, AV_LOG_ERROR, "Field %s differs: %s %s", opt->name, str1, str2);
                ret = AVERROR(EINVAL);
            }
            av_free(str1);
            av_free(str2);
        }
    }

    return ret;
}