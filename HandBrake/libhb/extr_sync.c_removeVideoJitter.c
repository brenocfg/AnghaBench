#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {double next_pts; int /*<<< orphan*/  in_queue; TYPE_4__* common; } ;
typedef  TYPE_6__ sync_stream_t ;
struct TYPE_14__ {double start; double duration; double stop; } ;
struct TYPE_16__ {TYPE_5__ s; } ;
typedef  TYPE_7__ hb_buffer_t ;
struct TYPE_13__ {TYPE_3__* job; } ;
struct TYPE_12__ {TYPE_2__* title; } ;
struct TYPE_10__ {int den; int num; } ;
struct TYPE_11__ {TYPE_1__ vrate; } ;

/* Variables and functions */
 TYPE_7__* hb_list_item (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void removeVideoJitter( sync_stream_t * stream, int stop )
{
    int           ii;
    hb_buffer_t * buf;
    double        frame_duration, next_pts;

    frame_duration = 90000. * stream->common->job->title->vrate.den /
                              stream->common->job->title->vrate.num;

    buf = hb_list_item(stream->in_queue, 0);
    buf->s.start = stream->next_pts;
    next_pts = stream->next_pts + frame_duration;
    for (ii = 1; ii <= stop; ii++)
    {
        buf->s.duration = frame_duration;
        buf->s.stop = next_pts;
        buf = hb_list_item(stream->in_queue, ii);
        buf->s.start = next_pts;
        next_pts += frame_duration;
    }
}