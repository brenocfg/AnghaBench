#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; TYPE_1__* comp; } ;
struct TYPE_4__ {int depth; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_PLANAR ; 
 TYPE_2__* av_pix_fmt_desc_get (int) ; 
 int ff_add_format (int /*<<< orphan*/ **,int) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterFormats *formats = NULL;
    int fmt, ret;

    for (fmt = 0; av_pix_fmt_desc_get(fmt); fmt++) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        if (desc->flags & AV_PIX_FMT_FLAG_PLANAR && !(desc->comp[0].depth & 7)
            && (ret = ff_add_format(&formats, fmt)) < 0)
                return ret;
    }

    return ff_set_common_formats(ctx, formats);
}