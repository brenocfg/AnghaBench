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
struct TYPE_7__ {int /*<<< orphan*/  mutex; TYPE_3__* state; int /*<<< orphan*/  threaded; } ;
typedef  TYPE_2__ zbar_processor_t ;
struct TYPE_6__ {int /*<<< orphan*/  num; } ;
struct TYPE_8__ {int /*<<< orphan*/ * kick_fds; TYPE_1__ polling; } ;
typedef  TYPE_3__ processor_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_cache_polling (TYPE_3__*) ; 
 int read (int /*<<< orphan*/ ,unsigned int*,int) ; 
 int /*<<< orphan*/  zprintf (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_kick_handler (zbar_processor_t *proc,
                              int i)
{
    processor_state_t *state = proc->state;
    zprintf(5, "kicking %d fds\n", state->polling.num);

    unsigned junk[2];
    int rc = read(state->kick_fds[0], junk, 2 * sizeof(unsigned));

    assert(proc->threaded);
    _zbar_mutex_lock(&proc->mutex);
    proc_cache_polling(proc->state);
    _zbar_mutex_unlock(&proc->mutex);
    return(rc);
}