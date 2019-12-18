#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ portBASE_TYPE ;
typedef  int /*<<< orphan*/  buf_stailq_t ;
struct TYPE_5__ {int owner; } ;
typedef  TYPE_1__ buf_desc_t ;
struct TYPE_6__ {int /*<<< orphan*/  recv_event; int /*<<< orphan*/  recv_link_list; } ;

/* Variables and functions */
 TYPE_1__* STAILQ_FIRST (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ * const,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ context ; 
 int /*<<< orphan*/  critical_enter_recv () ; 
 int /*<<< orphan*/  critical_exit_recv () ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  qe ; 
 int /*<<< orphan*/  recv_size_inc () ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void recv_flush_data(void)
{
    buf_stailq_t *const queue = &context.recv_link_list;

    critical_enter_recv();
    while(1) {
        portBASE_TYPE ret = xSemaphoreTake(context.recv_event, 0);
        if (ret == pdFALSE) break;

        buf_desc_t *desc = STAILQ_FIRST(queue);
        assert (desc != NULL && desc->owner == 0);
        STAILQ_REMOVE_HEAD(queue, qe);
        desc->owner = 1;
        STAILQ_INSERT_TAIL(queue, desc, qe);
        recv_size_inc();
        //we only add it to the tail here, without start the DMA nor increase buffer num.
    }
    critical_exit_recv();
}