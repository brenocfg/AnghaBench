#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int len; } ;
struct TYPE_23__ {unsigned int nb_inputs; unsigned int nb_outputs; TYPE_6__** outputs; TYPE_1__* filter; int /*<<< orphan*/  name; TYPE_6__** inputs; } ;
struct TYPE_22__ {unsigned int nb_filters; TYPE_8__** filters; } ;
struct TYPE_21__ {TYPE_5__* dstpad; TYPE_2__* dst; TYPE_4__* srcpad; TYPE_3__* src; } ;
struct TYPE_20__ {int /*<<< orphan*/  name; } ;
struct TYPE_19__ {int /*<<< orphan*/  name; } ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterGraph ;
typedef  TYPE_8__ AVFilterContext ;
typedef  TYPE_9__ AVBPrint ;

/* Variables and functions */
 unsigned int FFMAX (unsigned int,unsigned int) ; 
 unsigned int FFMAX3 (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  av_bprint_chars (TYPE_9__*,char,unsigned int) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_9__*,char*,...) ; 
 unsigned int print_link_prop (TYPE_9__*,TYPE_6__*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void avfilter_graph_dump_to_buf(AVBPrint *buf, AVFilterGraph *graph)
{
    unsigned i, j, x, e;

    for (i = 0; i < graph->nb_filters; i++) {
        AVFilterContext *filter = graph->filters[i];
        unsigned max_src_name = 0, max_dst_name = 0;
        unsigned max_in_name  = 0, max_out_name = 0;
        unsigned max_in_fmt   = 0, max_out_fmt  = 0;
        unsigned width, height, in_indent;
        unsigned lname = strlen(filter->name);
        unsigned ltype = strlen(filter->filter->name);

        for (j = 0; j < filter->nb_inputs; j++) {
            AVFilterLink *l = filter->inputs[j];
            unsigned ln = strlen(l->src->name) + 1 + strlen(l->srcpad->name);
            max_src_name = FFMAX(max_src_name, ln);
            max_in_name = FFMAX(max_in_name, strlen(l->dstpad->name));
            max_in_fmt = FFMAX(max_in_fmt, print_link_prop(NULL, l));
        }
        for (j = 0; j < filter->nb_outputs; j++) {
            AVFilterLink *l = filter->outputs[j];
            unsigned ln = strlen(l->dst->name) + 1 + strlen(l->dstpad->name);
            max_dst_name = FFMAX(max_dst_name, ln);
            max_out_name = FFMAX(max_out_name, strlen(l->srcpad->name));
            max_out_fmt = FFMAX(max_out_fmt, print_link_prop(NULL, l));
        }
        in_indent = max_src_name + max_in_name + max_in_fmt;
        in_indent += in_indent ? 4 : 0;
        width = FFMAX(lname + 2, ltype + 4);
        height = FFMAX3(2, filter->nb_inputs, filter->nb_outputs);
        av_bprint_chars(buf, ' ', in_indent);
        av_bprintf(buf, "+");
        av_bprint_chars(buf, '-', width);
        av_bprintf(buf, "+\n");
        for (j = 0; j < height; j++) {
            unsigned in_no  = j - (height - filter->nb_inputs ) / 2;
            unsigned out_no = j - (height - filter->nb_outputs) / 2;

            /* Input link */
            if (in_no < filter->nb_inputs) {
                AVFilterLink *l = filter->inputs[in_no];
                e = buf->len + max_src_name + 2;
                av_bprintf(buf, "%s:%s", l->src->name, l->srcpad->name);
                av_bprint_chars(buf, '-', e - buf->len);
                e = buf->len + max_in_fmt + 2 +
                    max_in_name - strlen(l->dstpad->name);
                print_link_prop(buf, l);
                av_bprint_chars(buf, '-', e - buf->len);
                av_bprintf(buf, "%s", l->dstpad->name);
            } else {
                av_bprint_chars(buf, ' ', in_indent);
            }

            /* Filter */
            av_bprintf(buf, "|");
            if (j == (height - 2) / 2) {
                x = (width - lname) / 2;
                av_bprintf(buf, "%*s%-*s", x, "", width - x, filter->name);
            } else if (j == (height - 2) / 2 + 1) {
                x = (width - ltype - 2) / 2;
                av_bprintf(buf, "%*s(%s)%*s", x, "", filter->filter->name,
                        width - ltype - 2 - x, "");
            } else {
                av_bprint_chars(buf, ' ', width);
            }
            av_bprintf(buf, "|");

            /* Output link */
            if (out_no < filter->nb_outputs) {
                AVFilterLink *l = filter->outputs[out_no];
                unsigned ln = strlen(l->dst->name) + 1 +
                              strlen(l->dstpad->name);
                e = buf->len + max_out_name + 2;
                av_bprintf(buf, "%s", l->srcpad->name);
                av_bprint_chars(buf, '-', e - buf->len);
                e = buf->len + max_out_fmt + 2 +
                    max_dst_name - ln;
                print_link_prop(buf, l);
                av_bprint_chars(buf, '-', e - buf->len);
                av_bprintf(buf, "%s:%s", l->dst->name, l->dstpad->name);
            }
            av_bprintf(buf, "\n");
        }
        av_bprint_chars(buf, ' ', in_indent);
        av_bprintf(buf, "+");
        av_bprint_chars(buf, '-', width);
        av_bprintf(buf, "+\n");
        av_bprintf(buf, "\n");
    }
}