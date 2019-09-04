#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ coding_method; } ;
typedef  TYPE_1__ Vp3Fragment ;
struct TYPE_6__ {int /*<<< orphan*/  last_frame; int /*<<< orphan*/  golden_frame; } ;
typedef  TYPE_2__ Vp3DecodeContext ;
typedef  int /*<<< orphan*/  ThreadFrame ;

/* Variables and functions */
 int /*<<< orphan*/  FFABS (int) ; 
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MODE_GOLDEN_MV ; 
 scalar_t__ MODE_USING_GOLDEN ; 
 int /*<<< orphan*/  ff_thread_await_progress (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void await_reference_row(Vp3DecodeContext *s, Vp3Fragment *fragment,
                                int motion_y, int y)
{
    ThreadFrame *ref_frame;
    int ref_row;
    int border = motion_y & 1;

    if (fragment->coding_method == MODE_USING_GOLDEN ||
        fragment->coding_method == MODE_GOLDEN_MV)
        ref_frame = &s->golden_frame;
    else
        ref_frame = &s->last_frame;

    ref_row = y + (motion_y >> 1);
    ref_row = FFMAX(FFABS(ref_row), ref_row + 8 + border);

    ff_thread_await_progress(ref_frame, ref_row, 0);
}