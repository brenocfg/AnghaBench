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
struct TYPE_9__ {scalar_t__ threads_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  tf; } ;
struct TYPE_7__ {int y; } ;
typedef  TYPE_1__ Mv ;
typedef  TYPE_2__ HEVCFrame ;
typedef  TYPE_3__ HEVCContext ;

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 scalar_t__ FF_THREAD_FRAME ; 
 int /*<<< orphan*/  ff_thread_await_progress (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hevc_await_progress(HEVCContext *s, HEVCFrame *ref,
                                const Mv *mv, int y0, int height)
{
    if (s->threads_type == FF_THREAD_FRAME ) {
        int y = FFMAX(0, (mv->y >> 2) + y0 + height + 9);

        ff_thread_await_progress(&ref->tf, y, 0);
    }
}