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
struct TYPE_5__ {int start; int flags; int /*<<< orphan*/  fps; int /*<<< orphan*/  rate; } ;
typedef  TYPE_1__ AVTimecode ;
typedef  int /*<<< orphan*/  AVRational ;

/* Variables and functions */
 int check_timecode (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  fps_from_frame_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int av_timecode_init(AVTimecode *tc, AVRational rate, int flags, int frame_start, void *log_ctx)
{
    memset(tc, 0, sizeof(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);
    return check_timecode(log_ctx, tc);
}