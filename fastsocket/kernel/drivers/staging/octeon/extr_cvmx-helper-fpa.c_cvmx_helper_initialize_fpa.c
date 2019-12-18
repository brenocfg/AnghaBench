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
 int /*<<< orphan*/  CVMX_FPA_DFA_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_DFA_POOL_SIZE ; 
 int /*<<< orphan*/  CVMX_FPA_OUTPUT_BUFFER_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE ; 
 int /*<<< orphan*/  CVMX_FPA_PACKET_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_PACKET_POOL_SIZE ; 
 int /*<<< orphan*/  CVMX_FPA_TIMER_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_TIMER_POOL_SIZE ; 
 int /*<<< orphan*/  CVMX_FPA_WQE_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_WQE_POOL_SIZE ; 
 int __cvmx_helper_initialize_fpa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int cvmx_helper_initialize_fpa(int packet_buffers, int work_queue_entries,
			       int pko_buffers, int tim_buffers,
			       int dfa_buffers)
{
#ifndef CVMX_FPA_PACKET_POOL
#define CVMX_FPA_PACKET_POOL -1
#define CVMX_FPA_PACKET_POOL_SIZE 0
#endif
#ifndef CVMX_FPA_WQE_POOL
#define CVMX_FPA_WQE_POOL -1
#define CVMX_FPA_WQE_POOL_SIZE 0
#endif
#ifndef CVMX_FPA_OUTPUT_BUFFER_POOL
#define CVMX_FPA_OUTPUT_BUFFER_POOL -1
#define CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE 0
#endif
#ifndef CVMX_FPA_TIMER_POOL
#define CVMX_FPA_TIMER_POOL -1
#define CVMX_FPA_TIMER_POOL_SIZE 0
#endif
#ifndef CVMX_FPA_DFA_POOL
#define CVMX_FPA_DFA_POOL -1
#define CVMX_FPA_DFA_POOL_SIZE 0
#endif
	return __cvmx_helper_initialize_fpa(CVMX_FPA_PACKET_POOL,
					    CVMX_FPA_PACKET_POOL_SIZE,
					    packet_buffers, CVMX_FPA_WQE_POOL,
					    CVMX_FPA_WQE_POOL_SIZE,
					    work_queue_entries,
					    CVMX_FPA_OUTPUT_BUFFER_POOL,
					    CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE,
					    pko_buffers, CVMX_FPA_TIMER_POOL,
					    CVMX_FPA_TIMER_POOL_SIZE,
					    tim_buffers, CVMX_FPA_DFA_POOL,
					    CVMX_FPA_DFA_POOL_SIZE,
					    dfa_buffers);
}