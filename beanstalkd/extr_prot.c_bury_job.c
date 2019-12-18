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
struct TYPE_16__ {int /*<<< orphan*/  buried_ct; } ;
struct TYPE_13__ {int /*<<< orphan*/  bury_ct; int /*<<< orphan*/  state; } ;
struct TYPE_15__ {int walresv; TYPE_3__ r; int /*<<< orphan*/ * reserver; TYPE_2__* tube; } ;
struct TYPE_14__ {int /*<<< orphan*/  wal; } ;
struct TYPE_11__ {int /*<<< orphan*/  buried_ct; } ;
struct TYPE_12__ {TYPE_1__ stat; int /*<<< orphan*/  buried; } ;
typedef  TYPE_4__ Server ;
typedef  TYPE_5__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  Buried ; 
 TYPE_8__ global_stat ; 
 int /*<<< orphan*/  job_list_insert (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  walmaint (int /*<<< orphan*/ *) ; 
 int walresvupdate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walwrite (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static int
bury_job(Server *s, Job *j, char update_store)
{
    if (update_store) {
        int z = walresvupdate(&s->wal);
        if (!z)
            return 0;
        j->walresv += z;
    }

    job_list_insert(&j->tube->buried, j);
    global_stat.buried_ct++;
    j->tube->stat.buried_ct++;
    j->r.state = Buried;
    j->reserver = NULL;
    j->r.bury_ct++;

    if (update_store) {
        if (!walwrite(&s->wal, j)) {
            return 0;
        }
        walmaint(&s->wal);
    }

    return 1;
}