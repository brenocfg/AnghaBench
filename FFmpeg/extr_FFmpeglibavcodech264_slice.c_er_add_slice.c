#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* h264; } ;
struct TYPE_6__ {TYPE_1__* slice_ctx; int /*<<< orphan*/  enable_er; } ;
struct TYPE_5__ {int /*<<< orphan*/  er; } ;
typedef  TYPE_3__ H264SliceContext ;
typedef  int /*<<< orphan*/  ERContext ;

/* Variables and functions */
 scalar_t__ CONFIG_ERROR_RESILIENCE ; 
 int /*<<< orphan*/  ff_er_add_slice (int /*<<< orphan*/ *,int,int,int,int,int) ; 

__attribute__((used)) static void er_add_slice(H264SliceContext *sl,
                         int startx, int starty,
                         int endx, int endy, int status)
{
    if (!sl->h264->enable_er)
        return;

    if (CONFIG_ERROR_RESILIENCE) {
        ERContext *er = &sl->h264->slice_ctx[0].er;

        ff_er_add_slice(er, startx, starty, endx, endy, status);
    }
}