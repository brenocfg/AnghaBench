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
struct TYPE_7__ {int /*<<< orphan*/  hsub; int /*<<< orphan*/  chroma; int /*<<< orphan*/  luma; int /*<<< orphan*/  vsub; } ;
typedef  TYPE_1__ UnsharpContext ;
struct TYPE_10__ {TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  w; TYPE_4__* dst; int /*<<< orphan*/  format; } ;
struct TYPE_8__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int init_filter_param (TYPE_4__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props(AVFilterLink *link)
{
    UnsharpContext *s = link->dst->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(link->format);
    int ret;

    s->hsub = desc->log2_chroma_w;
    s->vsub = desc->log2_chroma_h;

    ret = init_filter_param(link->dst, &s->luma,   "luma",   link->w);
    if (ret < 0)
        return ret;
    ret = init_filter_param(link->dst, &s->chroma, "chroma", AV_CEIL_RSHIFT(link->w, s->hsub));
    if (ret < 0)
        return ret;

    return 0;
}