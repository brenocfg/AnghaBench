#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int dummy; } ;
struct TYPE_5__ {int num; int /*<<< orphan*/  handlers; int /*<<< orphan*/  fds; } ;
struct TYPE_7__ {int num; int /*<<< orphan*/  handlers; int /*<<< orphan*/  fds; } ;
struct TYPE_6__ {TYPE_1__ polling; TYPE_4__ thr_polling; } ;
typedef  TYPE_2__ processor_state_t ;
typedef  int /*<<< orphan*/  poll_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_polls (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void proc_cache_polling (processor_state_t *state)
{
    /* make a thread-local copy of polling data */
    int n = state->thr_polling.num = state->polling.num;
    alloc_polls(&state->thr_polling);
    memcpy(state->thr_polling.fds, state->polling.fds,
           n * sizeof(struct pollfd));
    memcpy(state->thr_polling.handlers, state->polling.handlers,
           n * sizeof(poll_handler_t*));
}