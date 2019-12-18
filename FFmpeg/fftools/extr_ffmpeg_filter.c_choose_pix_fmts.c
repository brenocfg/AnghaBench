#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_15__ {int* pix_fmts; } ;
struct TYPE_14__ {scalar_t__ pix_fmt; scalar_t__ strict_std_compliance; int /*<<< orphan*/  codec_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  value; } ;
struct TYPE_12__ {TYPE_1__* graph; TYPE_2__* ost; } ;
struct TYPE_11__ {TYPE_5__* enc_ctx; TYPE_6__* enc; int /*<<< orphan*/  st; scalar_t__ keep_pix_fmt; int /*<<< orphan*/  encoder_opts; } ;
struct TYPE_10__ {int /*<<< orphan*/  graph; } ;
typedef  TYPE_2__ OutputStream ;
typedef  TYPE_3__ OutputFilter ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AVFILTER_AUTO_CONVERT_NONE ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 scalar_t__ FF_COMPLIANCE_UNOFFICIAL ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* av_get_pix_fmt_name (int const) ; 
 int /*<<< orphan*/  av_opt_set (TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* av_strdup (char*) ; 
 int /*<<< orphan*/  avfilter_graph_set_auto_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int const choose_pixel_fmt (int /*<<< orphan*/ ,TYPE_5__*,TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int* get_compliance_unofficial_pix_fmts (int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static char *choose_pix_fmts(OutputFilter *ofilter)
{
    OutputStream *ost = ofilter->ost;
    AVDictionaryEntry *strict_dict = av_dict_get(ost->encoder_opts, "strict", NULL, 0);
    if (strict_dict)
        // used by choose_pixel_fmt() and below
        av_opt_set(ost->enc_ctx, "strict", strict_dict->value, 0);

     if (ost->keep_pix_fmt) {
        avfilter_graph_set_auto_convert(ofilter->graph->graph,
                                            AVFILTER_AUTO_CONVERT_NONE);
        if (ost->enc_ctx->pix_fmt == AV_PIX_FMT_NONE)
            return NULL;
        return av_strdup(av_get_pix_fmt_name(ost->enc_ctx->pix_fmt));
    }
    if (ost->enc_ctx->pix_fmt != AV_PIX_FMT_NONE) {
        return av_strdup(av_get_pix_fmt_name(choose_pixel_fmt(ost->st, ost->enc_ctx, ost->enc, ost->enc_ctx->pix_fmt)));
    } else if (ost->enc && ost->enc->pix_fmts) {
        const enum AVPixelFormat *p;
        AVIOContext *s = NULL;
        uint8_t *ret;
        int len;

        if (avio_open_dyn_buf(&s) < 0)
            exit_program(1);

        p = ost->enc->pix_fmts;
        if (ost->enc_ctx->strict_std_compliance <= FF_COMPLIANCE_UNOFFICIAL) {
            p = get_compliance_unofficial_pix_fmts(ost->enc_ctx->codec_id, p);
        }

        for (; *p != AV_PIX_FMT_NONE; p++) {
            const char *name = av_get_pix_fmt_name(*p);
            avio_printf(s, "%s|", name);
        }
        len = avio_close_dyn_buf(s, &ret);
        ret[len - 1] = 0;
        return ret;
    } else
        return NULL;
}