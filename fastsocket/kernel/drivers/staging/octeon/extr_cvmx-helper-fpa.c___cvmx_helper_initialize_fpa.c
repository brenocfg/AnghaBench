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

/* Variables and functions */
 int __cvmx_helper_initialize_fpa_pool (int,int,int,char*) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 int /*<<< orphan*/  cvmx_fpa_enable () ; 

__attribute__((used)) static int __cvmx_helper_initialize_fpa(int pip_pool, int pip_size,
					int pip_buffers, int wqe_pool,
					int wqe_size, int wqe_entries,
					int pko_pool, int pko_size,
					int pko_buffers, int tim_pool,
					int tim_size, int tim_buffers,
					int dfa_pool, int dfa_size,
					int dfa_buffers)
{
	int status;

	cvmx_fpa_enable();

	if ((pip_buffers > 0) && (pip_buffers <= 64))
		cvmx_dprintf
		    ("Warning: %d packet buffers may not be enough for hardware"
		     " prefetch. 65 or more is recommended.\n", pip_buffers);

	if (pip_pool >= 0) {
		status =
		    __cvmx_helper_initialize_fpa_pool(pip_pool, pip_size,
						      pip_buffers,
						      "Packet Buffers");
		if (status)
			return status;
	}

	if (wqe_pool >= 0) {
		status =
		    __cvmx_helper_initialize_fpa_pool(wqe_pool, wqe_size,
						      wqe_entries,
						      "Work Queue Entries");
		if (status)
			return status;
	}

	if (pko_pool >= 0) {
		status =
		    __cvmx_helper_initialize_fpa_pool(pko_pool, pko_size,
						      pko_buffers,
						      "PKO Command Buffers");
		if (status)
			return status;
	}

	if (tim_pool >= 0) {
		status =
		    __cvmx_helper_initialize_fpa_pool(tim_pool, tim_size,
						      tim_buffers,
						      "TIM Command Buffers");
		if (status)
			return status;
	}

	if (dfa_pool >= 0) {
		status =
		    __cvmx_helper_initialize_fpa_pool(dfa_pool, dfa_size,
						      dfa_buffers,
						      "DFA Command Buffers");
		if (status)
			return status;
	}

	return 0;
}