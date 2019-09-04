#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ format; } ;
struct TYPE_9__ {scalar_t__ sw_format; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_PIX_FMT_OPENCL ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int opencl_map_frame (TYPE_1__*,TYPE_2__*,TYPE_2__ const*,int) ; 

__attribute__((used)) static int opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           const AVFrame *src, int flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    if (hwfc->sw_format != dst->format)
        return AVERROR(ENOSYS);
    return opencl_map_frame(hwfc, dst, src, flags);
}