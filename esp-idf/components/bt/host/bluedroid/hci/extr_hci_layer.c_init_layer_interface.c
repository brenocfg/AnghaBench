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
struct TYPE_2__ {int /*<<< orphan*/  transmit_downward; int /*<<< orphan*/  transmit_command_futured; int /*<<< orphan*/  transmit_command; } ;

/* Variables and functions */
 TYPE_1__ interface ; 
 int interface_created ; 
 int /*<<< orphan*/  transmit_command ; 
 int /*<<< orphan*/  transmit_command_futured ; 
 int /*<<< orphan*/  transmit_downward ; 

__attribute__((used)) static void init_layer_interface(void)
{
    if (!interface_created) {
        interface.transmit_command = transmit_command;
        interface.transmit_command_futured = transmit_command_futured;
        interface.transmit_downward = transmit_downward;
        interface_created = true;
    }
}