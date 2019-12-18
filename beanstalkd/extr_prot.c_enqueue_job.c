#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_16__ {int /*<<< orphan*/  urgent_ct; } ;
struct TYPE_11__ {scalar_t__ pri; int /*<<< orphan*/  state; scalar_t__ deadline_at; } ;
struct TYPE_15__ {TYPE_3__* tube; TYPE_1__ r; int /*<<< orphan*/ * reserver; } ;
struct TYPE_14__ {int /*<<< orphan*/  wal; } ;
struct TYPE_12__ {int /*<<< orphan*/  urgent_ct; } ;
struct TYPE_13__ {TYPE_2__ stat; int /*<<< orphan*/  ready; int /*<<< orphan*/  delay; } ;
typedef  TYPE_4__ Server ;
typedef  TYPE_5__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  Delayed ; 
 int /*<<< orphan*/  Ready ; 
 scalar_t__ URGENT_THRESHOLD ; 
 TYPE_8__ global_stat ; 
 int heapinsert (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ nanoseconds () ; 
 int /*<<< orphan*/  process_queue () ; 
 int /*<<< orphan*/  ready_ct ; 
 int /*<<< orphan*/  walmaint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walwrite (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static int
enqueue_job(Server *s, Job *j, int64 delay, char update_store)
{
    int r;

    j->reserver = NULL;
    if (delay) {
        j->r.deadline_at = nanoseconds() + delay;
        r = heapinsert(&j->tube->delay, j);
        if (!r)
            return 0;
        j->r.state = Delayed;
    } else {
        r = heapinsert(&j->tube->ready, j);
        if (!r)
            return 0;
        j->r.state = Ready;
        ready_ct++;
        if (j->r.pri < URGENT_THRESHOLD) {
            global_stat.urgent_ct++;
            j->tube->stat.urgent_ct++;
        }
    }

    if (update_store) {
        if (!walwrite(&s->wal, j)) {
            return 0;
        }
        walmaint(&s->wal);
    }

    // The call below makes this function do too much.
    // TODO: refactor this call outside so the call is explicit (not hidden)?
    process_queue();
    return 1;
}