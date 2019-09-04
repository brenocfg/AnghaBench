#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_11__ {int nb_channel_layouts; int /*<<< orphan*/ * channel_layouts; } ;
struct TYPE_10__ {int nb_inputs; int nb_outputs; int /*<<< orphan*/  output_pads; TYPE_2__** outputs; int /*<<< orphan*/  input_pads; TYPE_1__** inputs; } ;
struct TYPE_9__ {int nb_formats; int /*<<< orphan*/ * formats; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_5__* in_channel_layouts; TYPE_3__* in_formats; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_5__* out_channel_layouts; TYPE_3__* out_formats; } ;
typedef  TYPE_3__ AVFilterFormats ;
typedef  TYPE_4__ AVFilterContext ;
typedef  TYPE_5__ AVFilterChannelLayouts ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  av_get_channel_layout_string (char*,int,int,int /*<<< orphan*/ ) ; 
 char* av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 char* av_get_sample_fmt_name (int /*<<< orphan*/ ) ; 
 char* avfilter_pad_get_name (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*) ; 

__attribute__((used)) static void print_formats(AVFilterContext *filter_ctx)
{
    int i, j;

#define PRINT_FMTS(inout, outin, INOUT)                                 \
    for (i = 0; i < filter_ctx->nb_##inout##puts; i++) {                     \
        if (filter_ctx->inout##puts[i]->type == AVMEDIA_TYPE_VIDEO) {   \
            AVFilterFormats *fmts =                                     \
                filter_ctx->inout##puts[i]->outin##_formats;            \
            for (j = 0; j < fmts->nb_formats; j++)                    \
                if(av_get_pix_fmt_name(fmts->formats[j]))               \
                printf(#INOUT "PUT[%d] %s: fmt:%s\n",                   \
                       i, avfilter_pad_get_name(filter_ctx->inout##put_pads, i),      \
                       av_get_pix_fmt_name(fmts->formats[j]));          \
        } else if (filter_ctx->inout##puts[i]->type == AVMEDIA_TYPE_AUDIO) { \
            AVFilterFormats *fmts;                                      \
            AVFilterChannelLayouts *layouts;                            \
                                                                        \
            fmts = filter_ctx->inout##puts[i]->outin##_formats;         \
            for (j = 0; j < fmts->nb_formats; j++)                    \
                printf(#INOUT "PUT[%d] %s: fmt:%s\n",                   \
                       i, avfilter_pad_get_name(filter_ctx->inout##put_pads, i),      \
                       av_get_sample_fmt_name(fmts->formats[j]));       \
                                                                        \
            layouts = filter_ctx->inout##puts[i]->outin##_channel_layouts; \
            for (j = 0; j < layouts->nb_channel_layouts; j++) {                  \
                char buf[256];                                          \
                av_get_channel_layout_string(buf, sizeof(buf), -1,      \
                                             layouts->channel_layouts[j]);         \
                printf(#INOUT "PUT[%d] %s: chlayout:%s\n",              \
                       i, avfilter_pad_get_name(filter_ctx->inout##put_pads, i), buf); \
            }                                                           \
        }                                                               \
    }                                                                   \

    PRINT_FMTS(in,  out, IN);
    PRINT_FMTS(out, in,  OUT);
}