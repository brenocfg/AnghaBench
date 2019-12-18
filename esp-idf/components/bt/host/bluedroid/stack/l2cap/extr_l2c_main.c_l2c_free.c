#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * rcv_pending_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_cb_ptr ; 
 TYPE_1__ l2cb ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 

void l2c_free(void)
{
    list_free(l2cb.rcv_pending_q);
    l2cb.rcv_pending_q = NULL;
#if L2C_DYNAMIC_MEMORY
    FREE_AND_RESET(l2c_cb_ptr);
#endif
}