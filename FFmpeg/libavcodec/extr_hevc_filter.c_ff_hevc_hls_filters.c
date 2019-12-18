#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* sps; } ;
struct TYPE_8__ {TYPE_2__ ps; } ;
struct TYPE_6__ {int width; int height; } ;
typedef  TYPE_3__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_hevc_hls_filter (TYPE_3__*,int,int,int) ; 

void ff_hevc_hls_filters(HEVCContext *s, int x_ctb, int y_ctb, int ctb_size)
{
    int x_end = x_ctb >= s->ps.sps->width  - ctb_size;
    int y_end = y_ctb >= s->ps.sps->height - ctb_size;
    if (y_ctb && x_ctb)
        ff_hevc_hls_filter(s, x_ctb - ctb_size, y_ctb - ctb_size, ctb_size);
    if (y_ctb && x_end)
        ff_hevc_hls_filter(s, x_ctb, y_ctb - ctb_size, ctb_size);
    if (x_ctb && y_end)
        ff_hevc_hls_filter(s, x_ctb - ctb_size, y_ctb, ctb_size);
}