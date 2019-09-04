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
struct TYPE_5__ {scalar_t__ reference; } ;
struct TYPE_7__ {TYPE_2__* current_picture_ptr; TYPE_1__ current_picture; } ;
struct TYPE_6__ {int /*<<< orphan*/  tf; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  ff_thread_report_progress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_mpv_frame_end(MpegEncContext *s)
{
    emms_c();

    if (s->current_picture.reference)
        ff_thread_report_progress(&s->current_picture_ptr->tf, INT_MAX, 0);
}