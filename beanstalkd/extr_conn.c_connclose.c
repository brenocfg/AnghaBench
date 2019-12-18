#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ state; } ;
struct TYPE_17__ {TYPE_1__ r; } ;
struct TYPE_16__ {int fd; } ;
struct TYPE_15__ {int type; scalar_t__ in_conns; int /*<<< orphan*/  tickpos; TYPE_2__* srv; TYPE_11__* use; int /*<<< orphan*/  watch; scalar_t__ in_job_read; TYPE_6__* out_job; TYPE_6__* in_job; TYPE_4__ sock; } ;
struct TYPE_14__ {int /*<<< orphan*/  conns; } ;
struct TYPE_12__ {int /*<<< orphan*/  using_ct; } ;
typedef  TYPE_3__ Conn ;

/* Variables and functions */
 int CONN_TYPE_PRODUCER ; 
 int CONN_TYPE_WORKER ; 
 scalar_t__ Copy ; 
 int /*<<< orphan*/  TUBE_ASSIGN (TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  cur_conn_ct ; 
 int /*<<< orphan*/  cur_producer_ct ; 
 int /*<<< orphan*/  cur_worker_ct ; 
 int /*<<< orphan*/  enqueue_reserved_jobs (TYPE_3__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ has_reserved_job (TYPE_3__*) ; 
 int /*<<< orphan*/  heapremove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  job_free (TYPE_6__*) ; 
 int /*<<< orphan*/  ms_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  remove_waiting_conn (TYPE_3__*) ; 
 int /*<<< orphan*/  sockwant (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

void
connclose(Conn *c)
{
    sockwant(&c->sock, 0);
    close(c->sock.fd);
    if (verbose) {
        printf("close %d\n", c->sock.fd);
    }

    job_free(c->in_job);

    /* was this a peek or stats command? */
    if (c->out_job && c->out_job->r.state == Copy)
        job_free(c->out_job);

    c->in_job = c->out_job = NULL;
    c->in_job_read = 0;

    if (c->type & CONN_TYPE_PRODUCER) cur_producer_ct--; /* stats */
    if (c->type & CONN_TYPE_WORKER) cur_worker_ct--; /* stats */

    cur_conn_ct--; /* stats */

    remove_waiting_conn(c);
    if (has_reserved_job(c))
        enqueue_reserved_jobs(c);

    ms_clear(&c->watch);
    c->use->using_ct--;
    TUBE_ASSIGN(c->use, NULL);

    if (c->in_conns) {
        heapremove(&c->srv->conns, c->tickpos);
        c->in_conns = 0;
    }

    free(c);
}