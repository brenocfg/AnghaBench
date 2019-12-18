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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ acl_data_size_classic; int /*<<< orphan*/  readable; } ;

/* Variables and functions */
 scalar_t__ HCI_DATA_PREAMBLE_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ controller_param ; 

__attribute__((used)) static uint16_t get_acl_packet_size_classic(void)
{
    assert(controller_param.readable);
    return controller_param.acl_data_size_classic + HCI_DATA_PREAMBLE_SIZE;
}