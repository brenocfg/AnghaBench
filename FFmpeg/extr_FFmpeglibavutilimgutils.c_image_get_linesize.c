#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int log2_chroma_w; int flags; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_PIX_FMT_FLAG_BITSTREAM ; 
 int /*<<< orphan*/  EINVAL ; 
 int INT_MAX ; 

__attribute__((used)) static inline
int image_get_linesize(int width, int plane,
                       int max_step, int max_step_comp,
                       const AVPixFmtDescriptor *desc)
{
    int s, shifted_w, linesize;

    if (!desc)
        return AVERROR(EINVAL);

    if (width < 0)
        return AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = ((width + (1 << s) - 1)) >> s;
    if (shifted_w && max_step > INT_MAX / shifted_w)
        return AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    if (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize + 7) >> 3;
    return linesize;
}