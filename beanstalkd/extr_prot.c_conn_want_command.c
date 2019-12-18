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
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_8__ {TYPE_1__ r; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; scalar_t__ reply_sent; TYPE_3__* out_job; } ;
typedef  TYPE_2__ Conn ;

/* Variables and functions */
 scalar_t__ Copy ; 
 int /*<<< orphan*/  STATE_WANT_COMMAND ; 
 int /*<<< orphan*/  epollq_add (TYPE_2__*,char) ; 
 int /*<<< orphan*/  job_free (TYPE_3__*) ; 

__attribute__((used)) static void
conn_want_command(Conn *c)
{
    epollq_add(c, 'r');

    /* was this a peek or stats command? */
    if (c->out_job && c->out_job->r.state == Copy)
        job_free(c->out_job);
    c->out_job = NULL;

    c->reply_sent = 0; /* now that we're done, reset this */
    c->state = STATE_WANT_COMMAND;
}