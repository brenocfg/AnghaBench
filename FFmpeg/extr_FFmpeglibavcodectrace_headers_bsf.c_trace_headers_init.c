#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* cbc; int /*<<< orphan*/  fragment; } ;
typedef  TYPE_1__ TraceHeadersContext ;
struct TYPE_13__ {scalar_t__ extradata; int /*<<< orphan*/  codec_id; } ;
struct TYPE_12__ {int trace_enable; int /*<<< orphan*/  trace_level; } ;
struct TYPE_11__ {TYPE_5__* par_in; TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  CodedBitstreamFragment ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int ff_cbs_init (TYPE_4__**,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ff_cbs_read_extradata (TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static int trace_headers_init(AVBSFContext *bsf)
{
    TraceHeadersContext *ctx = bsf->priv_data;
    int err;

    err = ff_cbs_init(&ctx->cbc, bsf->par_in->codec_id, bsf);
    if (err < 0)
        return err;

    ctx->cbc->trace_enable = 1;
    ctx->cbc->trace_level  = AV_LOG_INFO;

    if (bsf->par_in->extradata) {
        CodedBitstreamFragment *frag = &ctx->fragment;

        av_log(bsf, AV_LOG_INFO, "Extradata\n");

        err = ff_cbs_read_extradata(ctx->cbc, frag, bsf->par_in);

        ff_cbs_fragment_reset(ctx->cbc, frag);
    }

    return err;
}