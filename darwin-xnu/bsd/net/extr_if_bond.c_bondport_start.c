#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bondport_ref ;

/* Variables and functions */
 int /*<<< orphan*/  LAEventStart ; 
 int /*<<< orphan*/  bondport_mux_machine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bondport_periodic_transmit_machine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bondport_receive_machine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bondport_transmit_machine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bondport_start(bondport_ref p)
{
    bondport_receive_machine(p, LAEventStart, NULL);
    bondport_mux_machine(p, LAEventStart, NULL);
    bondport_periodic_transmit_machine(p, LAEventStart, NULL);
    bondport_transmit_machine(p, LAEventStart, NULL);
    return;
}