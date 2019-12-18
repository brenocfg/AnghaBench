#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ pending_timeout; int /*<<< orphan*/  srv; TYPE_2__* out_job; } ;
struct TYPE_17__ {scalar_t__ deadline_at; int /*<<< orphan*/  timeout_ct; } ;
struct TYPE_18__ {TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;
typedef  TYPE_3__ Conn ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEADLINE_SOON ; 
 int /*<<< orphan*/  MSG_TIMED_OUT ; 
 int /*<<< orphan*/  bury_job (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ conn_waiting (TYPE_3__*) ; 
 scalar_t__ conndeadlinesoon (TYPE_3__*) ; 
 int /*<<< orphan*/  connsched (TYPE_3__*) ; 
 TYPE_2__* connsoonestjob (TYPE_3__*) ; 
 int enqueue_job (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* job_copy (TYPE_2__*) ; 
 scalar_t__ nanoseconds () ; 
 int /*<<< orphan*/  remove_this_reserved_job (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  remove_waiting_conn (TYPE_3__*) ; 
 int /*<<< orphan*/  reply_msg (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout_ct ; 

__attribute__((used)) static void
conn_timeout(Conn *c)
{
    int should_timeout = 0;
    Job *j;

    /* Check if the client was trying to reserve a job. */
    if (conn_waiting(c) && conndeadlinesoon(c))
        should_timeout = 1;

    /* Check if any reserved jobs have run out of time. We should do this
     * whether or not the client is waiting for a new reservation. */
    while ((j = connsoonestjob(c))) {
        if (j->r.deadline_at >= nanoseconds())
            break;

        /* This job is in the middle of being written out. If we return it to
         * the ready queue, someone might free it before we finish writing it
         * out to the socket. So we'll copy it here and free the copy when it's
         * done sending. */
        if (j == c->out_job) {
            c->out_job = job_copy(c->out_job);
        }

        timeout_ct++; /* stats */
        j->r.timeout_ct++;
        int r = enqueue_job(c->srv, remove_this_reserved_job(c, j), 0, 0);
        if (r < 1)
            bury_job(c->srv, j, 0); /* out of memory, so bury it */
        connsched(c);
    }

    if (should_timeout) {
        remove_waiting_conn(c);
        reply_msg(c, MSG_DEADLINE_SOON);
    } else if (conn_waiting(c) && c->pending_timeout >= 0) {
        c->pending_timeout = -1;
        remove_waiting_conn(c);
        reply_msg(c, MSG_TIMED_OUT);
    }
}