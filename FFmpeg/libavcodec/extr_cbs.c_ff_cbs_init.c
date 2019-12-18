#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_8__ {int /*<<< orphan*/  trace_level; scalar_t__ trace_enable; int /*<<< orphan*/ * decompose_unit_types; void* priv_data; TYPE_1__ const* codec; void* log_ctx; } ;
struct TYPE_7__ {int codec_id; int priv_data_size; } ;
typedef  TYPE_1__ CodedBitstreamType ;
typedef  TYPE_2__ CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (TYPE_1__**) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 void* av_mallocz (int) ; 
 TYPE_1__** cbs_type_table ; 

int ff_cbs_init(CodedBitstreamContext **ctx_ptr,
                enum AVCodecID codec_id, void *log_ctx)
{
    CodedBitstreamContext *ctx;
    const CodedBitstreamType *type;
    int i;

    type = NULL;
    for (i = 0; i < FF_ARRAY_ELEMS(cbs_type_table); i++) {
        if (cbs_type_table[i]->codec_id == codec_id) {
            type = cbs_type_table[i];
            break;
        }
    }
    if (!type)
        return AVERROR(EINVAL);

    ctx = av_mallocz(sizeof(*ctx));
    if (!ctx)
        return AVERROR(ENOMEM);

    ctx->log_ctx = log_ctx;
    ctx->codec   = type;

    ctx->priv_data = av_mallocz(ctx->codec->priv_data_size);
    if (!ctx->priv_data) {
        av_freep(&ctx);
        return AVERROR(ENOMEM);
    }

    ctx->decompose_unit_types = NULL;

    ctx->trace_enable = 0;
    ctx->trace_level  = AV_LOG_TRACE;

    *ctx_ptr = ctx;
    return 0;
}