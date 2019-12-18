#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  filter_ctx_label ;
typedef  int /*<<< orphan*/  dst_filter_ctx_label ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_14__ {char* name; int nb_outputs; TYPE_1__* filter; TYPE_4__** outputs; } ;
struct TYPE_13__ {int nb_filters; TYPE_6__** filters; } ;
struct TYPE_10__ {int num; int den; } ;
struct TYPE_12__ {scalar_t__ type; int w; int h; int sample_rate; TYPE_2__ time_base; int /*<<< orphan*/  format; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  dstpad; int /*<<< orphan*/  srcpad; TYPE_6__* dst; } ;
struct TYPE_11__ {char* name; } ;
struct TYPE_9__ {char* name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterGraph ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  av_get_channel_layout_string (char*,int,int,int /*<<< orphan*/ ) ; 
 char* av_get_sample_fmt_name (int /*<<< orphan*/ ) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 char* avfilter_pad_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static void print_digraph(FILE *outfile, AVFilterGraph *graph)
{
    int i, j;

    fprintf(outfile, "digraph G {\n");
    fprintf(outfile, "node [shape=box]\n");
    fprintf(outfile, "rankdir=LR\n");

    for (i = 0; i < graph->nb_filters; i++) {
        char filter_ctx_label[128];
        const AVFilterContext *filter_ctx = graph->filters[i];

        snprintf(filter_ctx_label, sizeof(filter_ctx_label), "%s\\n(%s)",
                 filter_ctx->name,
                 filter_ctx->filter->name);

        for (j = 0; j < filter_ctx->nb_outputs; j++) {
            AVFilterLink *link = filter_ctx->outputs[j];
            if (link) {
                char dst_filter_ctx_label[128];
                const AVFilterContext *dst_filter_ctx = link->dst;

                snprintf(dst_filter_ctx_label, sizeof(dst_filter_ctx_label),
                         "%s\\n(%s)",
                         dst_filter_ctx->name,
                         dst_filter_ctx->filter->name);

                fprintf(outfile, "\"%s\" -> \"%s\" [ label= \"inpad:%s -> outpad:%s\\n",
                        filter_ctx_label, dst_filter_ctx_label,
                        avfilter_pad_get_name(link->srcpad, 0),
                        avfilter_pad_get_name(link->dstpad, 0));

                if (link->type == AVMEDIA_TYPE_VIDEO) {
                    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(link->format);
                    fprintf(outfile,
                            "fmt:%s w:%d h:%d tb:%d/%d",
                            desc->name,
                            link->w, link->h,
                            link->time_base.num, link->time_base.den);
                } else if (link->type == AVMEDIA_TYPE_AUDIO) {
                    char buf[255];
                    av_get_channel_layout_string(buf, sizeof(buf), -1,
                                                 link->channel_layout);
                    fprintf(outfile,
                            "fmt:%s sr:%d cl:%s tb:%d/%d",
                            av_get_sample_fmt_name(link->format),
                            link->sample_rate, buf,
                            link->time_base.num, link->time_base.den);
                }
                fprintf(outfile, "\" ];\n");
            }
        }
    }
    fprintf(outfile, "}\n");
}