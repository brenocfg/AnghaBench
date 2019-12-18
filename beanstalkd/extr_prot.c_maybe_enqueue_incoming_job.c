#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ in_job_read; int /*<<< orphan*/  state; TYPE_2__* in_job; } ;
struct TYPE_6__ {scalar_t__ body_size; } ;
struct TYPE_7__ {TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;
typedef  TYPE_3__ Conn ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_WANT_DATA ; 
 int /*<<< orphan*/  enqueue_incoming_job (TYPE_3__*) ; 

__attribute__((used)) static void
maybe_enqueue_incoming_job(Conn *c)
{
    Job *j = c->in_job;

    /* do we have a complete job? */
    if (c->in_job_read == j->r.body_size) {
        enqueue_incoming_job(c);
        return;
    }

    /* otherwise we have incomplete data, so just keep waiting */
    c->state = STATE_WANT_DATA;
}