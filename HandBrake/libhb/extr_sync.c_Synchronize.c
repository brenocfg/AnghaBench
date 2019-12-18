#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * fifo_out; TYPE_3__* common; } ;
typedef  TYPE_2__ sync_stream_t ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  found_first_pts; TYPE_1__* job; scalar_t__ start_found; } ;
typedef  TYPE_3__ sync_common_t ;
struct TYPE_8__ {int /*<<< orphan*/ * die; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  OutputBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  checkFirstPts (TYPE_3__*) ; 
 int /*<<< orphan*/  fillQueues (TYPE_3__*) ; 
 scalar_t__ hb_fifo_full_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Synchronize( sync_stream_t * stream )
{
    sync_common_t * common = stream->common;

    // Sync deposits output directly into fifos, so work_loop is not
    // blocking when output fifos become full.  Wait here before
    // performing any output when the output fifo for the input stream
    // is full
    if (stream->fifo_out != NULL && common->start_found)
    {
        while (!common->job->done && !*common->job->die)
        {
            if (hb_fifo_full_wait(stream->fifo_out))
            {
                break;
            }
        }
    }

    hb_lock(common->mutex);

    if (!fillQueues(common))
    {
        hb_unlock(common->mutex);
        return;
    }
    if (!common->found_first_pts)
    {
        checkFirstPts(common);
    }
    OutputBuffer(common);

    hb_unlock(common->mutex);
}