#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_7__ {int nb_inputs; int nb_outputs; TYPE_1__* filter; int /*<<< orphan*/ * output_pads; int /*<<< orphan*/ * input_pads; } ;
struct TYPE_6__ {int /*<<< orphan*/  pad_idx; TYPE_3__* filter_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FilterGraph ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFilterPad ;
typedef  TYPE_2__ AVFilterInOut ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  avfilter_pad_get_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_close_dyn_buf (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_program (int) ; 

__attribute__((used)) static char *describe_filter_link(FilterGraph *fg, AVFilterInOut *inout, int in)
{
    AVFilterContext *ctx = inout->filter_ctx;
    AVFilterPad *pads = in ? ctx->input_pads  : ctx->output_pads;
    int       nb_pads = in ? ctx->nb_inputs   : ctx->nb_outputs;
    AVIOContext *pb;
    uint8_t *res = NULL;

    if (avio_open_dyn_buf(&pb) < 0)
        exit_program(1);

    avio_printf(pb, "%s", ctx->filter->name);
    if (nb_pads > 1)
        avio_printf(pb, ":%s", avfilter_pad_get_name(pads, inout->pad_idx));
    avio_w8(pb, 0);
    avio_close_dyn_buf(pb, &res);
    return res;
}