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
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ signal_user_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ghb_queue_buttons_grey (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_queue_remove_row_internal (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ghb_save_queue (int /*<<< orphan*/ ) ; 

void
ghb_queue_remove_row(signal_user_data_t *ud, int index)
{
    ghb_queue_remove_row_internal(ud, index);
    ghb_save_queue(ud->queue);
    ghb_queue_buttons_grey(ud);
}