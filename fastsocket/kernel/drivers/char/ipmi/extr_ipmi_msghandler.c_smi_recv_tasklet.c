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
typedef  int /*<<< orphan*/  ipmi_smi_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_new_recv_msgs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smi_recv_tasklet(unsigned long val)
{
	handle_new_recv_msgs((ipmi_smi_t) val);
}