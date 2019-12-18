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
typedef  void* int64_t ;
struct TYPE_4__ {void* end_time; void* startv_time; void* start_time; } ;
typedef  TYPE_1__ CCaptionSubContext ;

/* Variables and functions */
 int capture_screen (TYPE_1__*) ; 

__attribute__((used)) static int reap_screen(CCaptionSubContext *ctx, int64_t pts)
{
    ctx->start_time = ctx->startv_time;
    ctx->startv_time = pts;
    ctx->end_time = pts;
    return capture_screen(ctx);
}