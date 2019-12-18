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
struct TYPE_5__ {int pending_timeout; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Conn ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_WAIT ; 
 int /*<<< orphan*/  enqueue_waiting_conn (TYPE_1__*) ; 
 int /*<<< orphan*/  epollq_add (TYPE_1__*,char) ; 

__attribute__((used)) static void
wait_for_job(Conn *c, int timeout)
{
    c->state = STATE_WAIT;
    enqueue_waiting_conn(c);

    /* Set the pending timeout to the requested timeout amount */
    c->pending_timeout = timeout;

    // only care if they hang up
    epollq_add(c, 'h');
}