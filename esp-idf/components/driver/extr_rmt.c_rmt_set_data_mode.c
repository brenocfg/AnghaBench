#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rmt_data_mode_t ;
struct TYPE_3__ {int /*<<< orphan*/  fifo_mask; } ;
struct TYPE_4__ {TYPE_1__ apb_conf; } ;

/* Variables and functions */
 TYPE_2__ RMT ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmt_spinlock ; 

__attribute__((used)) static void rmt_set_data_mode(rmt_data_mode_t data_mode)
{
    portENTER_CRITICAL(&rmt_spinlock);
    RMT.apb_conf.fifo_mask = data_mode;
    portEXIT_CRITICAL(&rmt_spinlock);
}