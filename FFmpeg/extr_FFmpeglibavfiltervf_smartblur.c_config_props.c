#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_9__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_8__ {int /*<<< orphan*/  sws_flags; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; int /*<<< orphan*/  chroma; int /*<<< orphan*/  luma; } ;
struct TYPE_7__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ SmartblurContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_sws_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props(AVFilterLink *inlink)
{
    SmartblurContext *s = inlink->dst->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);

    s->hsub = desc->log2_chroma_w;
    s->vsub = desc->log2_chroma_h;

    alloc_sws_context(&s->luma, inlink->w, inlink->h, s->sws_flags);
    alloc_sws_context(&s->chroma,
                      AV_CEIL_RSHIFT(inlink->w, s->hsub),
                      AV_CEIL_RSHIFT(inlink->h, s->vsub),
                      s->sws_flags);

    return 0;
}