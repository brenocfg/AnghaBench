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
typedef  int /*<<< orphan*/  u8 ;
struct efx_ptp_timeset {unsigned int host_start; unsigned int host_end; unsigned int window; void* waitns; void* nanoseconds; void* seconds; } ;

/* Variables and functions */
 void* MCDI_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MC_NANOSECOND_MASK ; 
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  PTP_OUT_SYNCHRONIZE_HOSTEND ; 
 int /*<<< orphan*/  PTP_OUT_SYNCHRONIZE_HOSTSTART ; 
 int /*<<< orphan*/  PTP_OUT_SYNCHRONIZE_NANOSECONDS ; 
 int /*<<< orphan*/  PTP_OUT_SYNCHRONIZE_SECONDS ; 
 int /*<<< orphan*/  PTP_OUT_SYNCHRONIZE_WAITNS ; 

__attribute__((used)) static void efx_ptp_read_timeset(u8 *data, struct efx_ptp_timeset *timeset)
{
	unsigned start_ns, end_ns;

	timeset->host_start = MCDI_DWORD(data, PTP_OUT_SYNCHRONIZE_HOSTSTART);
	timeset->seconds = MCDI_DWORD(data, PTP_OUT_SYNCHRONIZE_SECONDS);
	timeset->nanoseconds = MCDI_DWORD(data,
					 PTP_OUT_SYNCHRONIZE_NANOSECONDS);
	timeset->host_end = MCDI_DWORD(data, PTP_OUT_SYNCHRONIZE_HOSTEND),
	timeset->waitns = MCDI_DWORD(data, PTP_OUT_SYNCHRONIZE_WAITNS);

	/* Ignore seconds */
	start_ns = timeset->host_start & MC_NANOSECOND_MASK;
	end_ns = timeset->host_end & MC_NANOSECOND_MASK;
	/* Allow for rollover */
	if (end_ns < start_ns)
		end_ns += NSEC_PER_SEC;
	/* Determine duration of operation */
	timeset->window = end_ns - start_ns;
}