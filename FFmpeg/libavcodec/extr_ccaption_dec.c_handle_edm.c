#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Screen {scalar_t__ row_used; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int active_screen; scalar_t__ real_time; struct Screen* screen; } ;
typedef  TYPE_1__ CCaptionSubContext ;

/* Variables and functions */
 int /*<<< orphan*/  reap_screen (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_edm(CCaptionSubContext *ctx, int64_t pts)
{
    struct Screen *screen = ctx->screen + ctx->active_screen;

    // In buffered mode, keep writing to screen until it is wiped.
    // Before wiping the display, capture contents to emit subtitle.
    if (!ctx->real_time)
        reap_screen(ctx, pts);

    screen->row_used = 0;

    // In realtime mode, emit an empty caption so the last one doesn't
    // stay on the screen.
    if (ctx->real_time)
        reap_screen(ctx, pts);
}