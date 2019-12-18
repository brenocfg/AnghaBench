#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_9__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_8__ {scalar_t__ type; char* name; } ;
struct TYPE_7__ {int /*<<< orphan*/ * codec; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVOption ;
typedef  TYPE_3__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_OPT_TYPE_CONST ; 
 int /*<<< orphan*/  av_free (char*) ; 
 scalar_t__ av_opt_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char**) ; 
 TYPE_2__* av_opt_next (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void dump_video_streams(const AVFormatContext *fmt_ctx, int decode)
{
    int i;

    for (i = 0; i < fmt_ctx->nb_streams; i++) {
        const AVOption *opt = NULL;
        const AVStream *st = fmt_ctx->streams[i];
        AVCodecContext *codec_ctx = st->codec;

        printf("stream=%d, decode=%d\n", i, decode);
        while (opt = av_opt_next(codec_ctx, opt)) {
            uint8_t *str;

            if (opt->type == AV_OPT_TYPE_CONST)
                continue;

            if (!strcmp(opt->name, "frame_number"))
                continue;

            if (av_opt_get(codec_ctx, opt->name, 0, &str) >= 0) {
                printf("    %s=%s\n", opt->name, str);
                av_free(str);
            }
        }
    }
}