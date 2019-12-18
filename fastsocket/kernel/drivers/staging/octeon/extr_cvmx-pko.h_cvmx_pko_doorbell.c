#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_3__ {int is_io; void* queue; void* port; int /*<<< orphan*/  did; int /*<<< orphan*/  mem_space; } ;
struct TYPE_4__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_pko_doorbell_address_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_IO_SEG ; 
 int /*<<< orphan*/  CVMX_OCT_DID_PKT_SEND ; 
 int /*<<< orphan*/  CVMX_SYNCWS ; 
 int /*<<< orphan*/  cvmx_write_io (scalar_t__,void*) ; 

__attribute__((used)) static inline void cvmx_pko_doorbell(uint64_t port, uint64_t queue,
				     uint64_t len)
{
	cvmx_pko_doorbell_address_t ptr;

	ptr.u64 = 0;
	ptr.s.mem_space = CVMX_IO_SEG;
	ptr.s.did = CVMX_OCT_DID_PKT_SEND;
	ptr.s.is_io = 1;
	ptr.s.port = port;
	ptr.s.queue = queue;
	/*
	 * Need to make sure output queue data is in DRAM before
	 * doorbell write.
	 */
	CVMX_SYNCWS;
	cvmx_write_io(ptr.u64, len);
}