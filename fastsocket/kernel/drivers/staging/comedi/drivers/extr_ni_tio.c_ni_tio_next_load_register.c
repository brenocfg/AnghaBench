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
 unsigned int const Gi_Next_Load_Source_Bit (int /*<<< orphan*/ ) ; 
 int NITIO_Gi_LoadA_Reg (int /*<<< orphan*/ ) ; 
 int NITIO_Gi_LoadB_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gxx_Status_Reg (int /*<<< orphan*/ ) ; 
 unsigned int read_register (struct ni_gpct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned ni_tio_next_load_register(struct ni_gpct *counter)
{
	const unsigned bits = read_register(counter,
					    NITIO_Gxx_Status_Reg(counter->
								 counter_index));

	if (bits & Gi_Next_Load_Source_Bit(counter->counter_index)) {
		return NITIO_Gi_LoadB_Reg(counter->counter_index);
	} else {
		return NITIO_Gi_LoadA_Reg(counter->counter_index);
	}
}