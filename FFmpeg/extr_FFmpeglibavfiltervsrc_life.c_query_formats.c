#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  draw; int /*<<< orphan*/  death_color; int /*<<< orphan*/  life_color; scalar_t__ mold; } ;
typedef  TYPE_1__ LifeContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AV_PIX_FMT_MONOBLACK ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_RGB24 ; 
 int /*<<< orphan*/ * ff_make_format_list (int*) ; 
 int ff_set_common_formats (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_picture_monoblack ; 
 int /*<<< orphan*/  fill_picture_rgb ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    LifeContext *life = ctx->priv;
    enum AVPixelFormat pix_fmts[] = { AV_PIX_FMT_NONE, AV_PIX_FMT_NONE };
    AVFilterFormats *fmts_list;

    if (life->mold || memcmp(life-> life_color, "\xff\xff\xff", 3)
                   || memcmp(life->death_color, "\x00\x00\x00", 3)) {
        pix_fmts[0] = AV_PIX_FMT_RGB24;
        life->draw = fill_picture_rgb;
    } else {
        pix_fmts[0] = AV_PIX_FMT_MONOBLACK;
        life->draw = fill_picture_monoblack;
    }

    fmts_list = ff_make_format_list(pix_fmts);
    return ff_set_common_formats(ctx, fmts_list);
}