#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int (* fmt_fn ) (int /*<<< orphan*/ *,int,void*) ;
struct TYPE_7__ {int body_size; int /*<<< orphan*/  state; } ;
struct TYPE_9__ {TYPE_1__ r; int /*<<< orphan*/ * body; } ;
struct TYPE_8__ {scalar_t__ out_job_sent; TYPE_6__* out_job; } ;
typedef  TYPE_2__ Conn ;

/* Variables and functions */
 int /*<<< orphan*/  Copy ; 
 int /*<<< orphan*/  MSG_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MSG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  STATE_SEND_JOB ; 
 TYPE_6__* allocate_job (int) ; 
 int /*<<< orphan*/  reply_line (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reply_serr (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_stats(Conn *c, fmt_fn fmt, void *data)
{
    int r, stats_len;

    /* first, measure how big a buffer we will need */
    stats_len = fmt(NULL, 0, data) + 16;

    c->out_job = allocate_job(stats_len); /* fake job to hold stats data */
    if (!c->out_job) {
        reply_serr(c, MSG_OUT_OF_MEMORY);
        return;
    }

    /* Mark this job as a copy so it can be appropriately freed later on */
    c->out_job->r.state = Copy;

    /* now actually format the stats data */
    r = fmt(c->out_job->body, stats_len, data);
    /* and set the actual body size */
    c->out_job->r.body_size = r;
    if (r > stats_len) {
        reply_serr(c, MSG_INTERNAL_ERROR);
        return;
    }

    c->out_job_sent = 0;
    reply_line(c, STATE_SEND_JOB, "OK %d\r\n", r - 2);
}