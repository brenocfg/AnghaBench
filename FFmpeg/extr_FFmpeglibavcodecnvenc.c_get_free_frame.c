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
typedef  int /*<<< orphan*/  tmp_surf ;
struct TYPE_3__ {int /*<<< orphan*/  unused_surface_queue; } ;
typedef  int /*<<< orphan*/  NvencSurface ;
typedef  TYPE_1__ NvencContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 scalar_t__ av_fifo_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static NvencSurface *get_free_frame(NvencContext *ctx)
{
    NvencSurface *tmp_surf;

    if (!(av_fifo_size(ctx->unused_surface_queue) > 0))
        // queue empty
        return NULL;

    av_fifo_generic_read(ctx->unused_surface_queue, &tmp_surf, sizeof(tmp_surf), NULL);
    return tmp_surf;
}