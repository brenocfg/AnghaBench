#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {TYPE_1__* in; } ;
struct TYPE_6__ {int have_next; scalar_t__ state; scalar_t__ after; int /*<<< orphan*/  pts_next; int /*<<< orphan*/ * frame_next; scalar_t__ sync; int /*<<< orphan*/  pts; } ;
typedef  TYPE_2__ FFFrameSync ;

/* Variables and functions */
 scalar_t__ EXT_INFINITY ; 
 int /*<<< orphan*/  INT64_MAX ; 
 scalar_t__ STATE_RUN ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  framesync_pts_extrapolate (TYPE_2__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framesync_sync_level_update (TYPE_2__*) ; 

__attribute__((used)) static void framesync_inject_status(FFFrameSync *fs, unsigned in, int status, int64_t pts)
{
    av_assert0(!fs->in[in].have_next);
    pts = fs->in[in].state != STATE_RUN || fs->in[in].after == EXT_INFINITY
        ? INT64_MAX : framesync_pts_extrapolate(fs, in, fs->in[in].pts);
    fs->in[in].sync = 0;
    framesync_sync_level_update(fs);
    fs->in[in].frame_next = NULL;
    fs->in[in].pts_next   = pts;
    fs->in[in].have_next  = 1;
}