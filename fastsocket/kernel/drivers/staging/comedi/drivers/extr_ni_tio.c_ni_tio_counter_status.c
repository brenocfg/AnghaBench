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
 unsigned int COMEDI_COUNTER_ARMED ; 
 unsigned int COMEDI_COUNTER_COUNTING ; 
 unsigned int const Gi_Armed_Bit (int /*<<< orphan*/ ) ; 
 unsigned int const Gi_Counting_Bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gxx_Status_Reg (int /*<<< orphan*/ ) ; 
 unsigned int read_register (struct ni_gpct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ni_tio_counter_status(struct ni_gpct *counter)
{
	unsigned int status = 0;
	const unsigned bits = read_register(counter,
					    NITIO_Gxx_Status_Reg(counter->
								 counter_index));
	if (bits & Gi_Armed_Bit(counter->counter_index)) {
		status |= COMEDI_COUNTER_ARMED;
		if (bits & Gi_Counting_Bit(counter->counter_index))
			status |= COMEDI_COUNTER_COUNTING;
	}
	return status;
}