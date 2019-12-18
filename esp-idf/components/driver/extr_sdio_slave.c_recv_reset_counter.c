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
struct TYPE_5__ {int owner; } ;
typedef  TYPE_1__ buf_desc_t ;

/* Variables and functions */
 TYPE_1__* STAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  critical_enter_recv () ; 
 int /*<<< orphan*/  critical_exit_recv () ; 
 int /*<<< orphan*/  qe ; 
 TYPE_1__* recv_get_first_empty_buf () ; 
 int /*<<< orphan*/  recv_size_inc () ; 
 int /*<<< orphan*/  recv_size_reset () ; 

__attribute__((used)) static void recv_reset_counter(void)
{
    recv_size_reset();

    critical_enter_recv();
    buf_desc_t *desc = recv_get_first_empty_buf();
    while (desc != NULL) {
        assert(desc->owner == 1);
        recv_size_inc();
        desc = STAILQ_NEXT(desc, qe);
    }
    critical_exit_recv();
}