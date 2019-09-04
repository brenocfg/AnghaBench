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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ index_ptr; scalar_t__ buffer; } ;

/* Variables and functions */
 scalar_t__ ENTROPY_BUFFER_SIZE ; 
 TYPE_1__ EntropyData ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cpu_number () ; 
 scalar_t__ master_cpu ; 
 int /*<<< orphan*/  rdtsc_nofence (int,int) ; 
 int ror32 (int,int) ; 

void
ml_entropy_collect(void)
{
	uint32_t	tsc_lo, tsc_hi;
	uint32_t	*ep;

	assert(cpu_number() == master_cpu);

	/* update buffer pointer cyclically */
	if (EntropyData.index_ptr - EntropyData.buffer == ENTROPY_BUFFER_SIZE)
		ep = EntropyData.index_ptr = EntropyData.buffer;
	else
		ep = EntropyData.index_ptr++;

	rdtsc_nofence(tsc_lo, tsc_hi);
	*ep = ror32(*ep, 9) ^ tsc_lo;
}