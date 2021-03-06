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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int avfmt; int /*<<< orphan*/  v4l2_fmt; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* fmt_map ; 

uint32_t ff_v4l2_format_avfmt_to_v4l2(enum AVPixelFormat avfmt)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(fmt_map); i++) {
        if (fmt_map[i].avfmt == avfmt)
            return fmt_map[i].v4l2_fmt;
    }
    return 0;
}