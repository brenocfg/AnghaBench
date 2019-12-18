#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64 ;
struct TYPE_9__ {scalar_t__ state; int deadline_at; int created_at; int delay; int ttr; int /*<<< orphan*/  kick_ct; int /*<<< orphan*/  bury_ct; int /*<<< orphan*/  release_ct; int /*<<< orphan*/  timeout_ct; int /*<<< orphan*/  reserve_ct; int /*<<< orphan*/  pri; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_3__ r; TYPE_2__* tube; TYPE_1__* file; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int seq; } ;
typedef  TYPE_4__ Job ;

/* Variables and functions */
 scalar_t__ Delayed ; 
 scalar_t__ Reserved ; 
 char* STATS_JOB_FMT ; 
 int /*<<< orphan*/  job_state (TYPE_4__*) ; 
 int nanoseconds () ; 
 int snprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fmt_job_stats(char *buf, size_t size, Job *j)
{
    int64 t;
    int64 time_left;
    int file = 0;

    t = nanoseconds();
    if (j->r.state == Reserved || j->r.state == Delayed) {
        time_left = (j->r.deadline_at - t) / 1000000000;
    } else {
        time_left = 0;
    }
    if (j->file) {
        file = j->file->seq;
    }
    return snprintf(buf, size, STATS_JOB_FMT,
            j->r.id,
            j->tube->name,
            job_state(j),
            j->r.pri,
            (t - j->r.created_at) / 1000000000,
            j->r.delay / 1000000000,
            j->r.ttr / 1000000000,
            time_left,
            file,
            j->r.reserve_ct,
            j->r.timeout_ct,
            j->r.release_ct,
            j->r.bury_ct,
            j->r.kick_ct);
}