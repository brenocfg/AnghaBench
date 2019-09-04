#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int active_screen; scalar_t__ real_time; scalar_t__ cursor_column; } ;
typedef  TYPE_1__ CCaptionSubContext ;

/* Variables and functions */
 int /*<<< orphan*/  handle_edm (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reap_screen (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_eoc(CCaptionSubContext *ctx, int64_t pts)
{
    // In buffered mode, we wait til the *next* EOC and
    // reap what was already on the screen since the last EOC.
    if (!ctx->real_time)
        handle_edm(ctx,pts);

    ctx->active_screen = !ctx->active_screen;
    ctx->cursor_column = 0;

    // In realtime mode, we display the buffered contents (after
    // flipping the buffer to active above) as soon as EOC arrives.
    if (ctx->real_time)
        reap_screen(ctx, pts);
}