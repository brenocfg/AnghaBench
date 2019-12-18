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
struct ni_gpct {int /*<<< orphan*/  counter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  Gi_Reset_Bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gxx_Joint_Reset_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_register (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_tio_reset_count_and_disarm(struct ni_gpct *counter)
{
	write_register(counter, Gi_Reset_Bit(counter->counter_index),
		       NITIO_Gxx_Joint_Reset_Reg(counter->counter_index));
}