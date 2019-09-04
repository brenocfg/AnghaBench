#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__** buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  source; } ;
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_2__ HWMapDescriptor ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int av_frame_ref (int /*<<< orphan*/ ,TYPE_3__ const*) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 

int ff_hwframe_map_replace(AVFrame *dst, const AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    av_frame_unref(hwmap->source);
    return av_frame_ref(hwmap->source, src);
}