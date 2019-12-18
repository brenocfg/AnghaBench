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
typedef  int /*<<< orphan*/  tSMP_BR_STATE ;
struct TYPE_2__ {int /*<<< orphan*/  br_state; } ;

/* Variables and functions */
 TYPE_1__ smp_cb ; 

tSMP_BR_STATE smp_get_br_state(void)
{
    return smp_cb.br_state;
}