#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int addr; int back; int /*<<< orphan*/  pool; } ;
union cvmx_buf_ptr {TYPE_3__ s; } ;
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ bufs; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_10__ {union cvmx_buf_ptr packet_ptr; TYPE_2__ word2; } ;
typedef  TYPE_4__ cvmx_wqe_t ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_fpa_free (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_phys_to_ptr (scalar_t__) ; 
 scalar_t__ cvmx_ptr_to_phys (TYPE_4__*) ; 

__attribute__((used)) static inline void cvmx_helper_free_packet_data(cvmx_wqe_t *work)
{
	uint64_t number_buffers;
	union cvmx_buf_ptr buffer_ptr;
	union cvmx_buf_ptr next_buffer_ptr;
	uint64_t start_of_buffer;

	number_buffers = work->word2.s.bufs;
	if (number_buffers == 0)
		return;
	buffer_ptr = work->packet_ptr;

	/*
	 * Since the number of buffers is not zero, we know this is
	 * not a dynamic short packet. We need to check if it is a
	 * packet received with IPD_CTL_STATUS[NO_WPTR]. If this is
	 * true, we need to free all buffers except for the first
	 * one. The caller doesn't expect their WQE pointer to be
	 * freed
	 */
	start_of_buffer = ((buffer_ptr.s.addr >> 7) - buffer_ptr.s.back) << 7;
	if (cvmx_ptr_to_phys(work) == start_of_buffer) {
		next_buffer_ptr =
		    *(union cvmx_buf_ptr *) cvmx_phys_to_ptr(buffer_ptr.s.addr - 8);
		buffer_ptr = next_buffer_ptr;
		number_buffers--;
	}

	while (number_buffers--) {
		/*
		 * Remember the back pointer is in cache lines, not
		 * 64bit words
		 */
		start_of_buffer =
		    ((buffer_ptr.s.addr >> 7) - buffer_ptr.s.back) << 7;
		/*
		 * Read pointer to next buffer before we free the
		 * current buffer.
		 */
		next_buffer_ptr =
		    *(union cvmx_buf_ptr *) cvmx_phys_to_ptr(buffer_ptr.s.addr - 8);
		cvmx_fpa_free(cvmx_phys_to_ptr(start_of_buffer),
			      buffer_ptr.s.pool, 0);
		buffer_ptr = next_buffer_ptr;
	}
}