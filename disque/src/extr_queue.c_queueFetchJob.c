#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sl; int /*<<< orphan*/  jobs_out; int /*<<< orphan*/  atime; } ;
typedef  TYPE_1__ queue ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ job ;
struct TYPE_9__ {int /*<<< orphan*/  unixtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_FLAG_DELIVERED ; 
 int /*<<< orphan*/  JOB_STATE_ACTIVE ; 
 TYPE_4__ server ; 
 unsigned long skiplistLength (int /*<<< orphan*/ ) ; 
 TYPE_2__* skiplistPopHead (int /*<<< orphan*/ ) ; 

job *queueFetchJob(queue *q, unsigned long *qlen) {
    if (skiplistLength(q->sl) == 0) return NULL;
    job *j = skiplistPopHead(q->sl);
    j->state = JOB_STATE_ACTIVE;
    j->flags |= JOB_FLAG_DELIVERED;
    q->atime = server.unixtime;
    q->jobs_out++;
    if (qlen) *qlen = skiplistLength(q->sl);
    return j;
}