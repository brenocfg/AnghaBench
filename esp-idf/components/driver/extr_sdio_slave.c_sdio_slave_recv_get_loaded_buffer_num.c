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
typedef  int /*<<< orphan*/  buf_stailq_t ;
struct TYPE_2__ {int /*<<< orphan*/  recv_link_list; } ;

/* Variables and functions */
 TYPE_1__ context ; 
 int /*<<< orphan*/  dump_queue (int /*<<< orphan*/ * const) ; 

__attribute__((used)) static void __attribute((unused)) sdio_slave_recv_get_loaded_buffer_num(void)
{
    buf_stailq_t *const queue = &context.recv_link_list;
    dump_queue(queue);
}