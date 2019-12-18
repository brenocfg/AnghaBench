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
struct TYPE_3__ {int /*<<< orphan*/  axis_h; int /*<<< orphan*/  width; int /*<<< orphan*/  format; int /*<<< orphan*/  axis_frame; } ;
typedef  TYPE_1__ ShowCQTContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  alloc_frame_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_axis_pixel_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_axis_empty(ShowCQTContext *s)
{
    if (!(s->axis_frame = alloc_frame_empty(convert_axis_pixel_format(s->format), s->width, s->axis_h)))
        return AVERROR(ENOMEM);
    return 0;
}