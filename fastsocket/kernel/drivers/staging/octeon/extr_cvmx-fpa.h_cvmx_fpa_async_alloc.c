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
typedef  int uint64_t ;
struct TYPE_3__ {int scraddr; int len; scalar_t__ addr; int /*<<< orphan*/  did; } ;
struct TYPE_4__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_fpa_iobdma_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_FULL_DID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CVMX_OCT_DID_FPA ; 
 int /*<<< orphan*/  cvmx_send_single (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_fpa_async_alloc(uint64_t scr_addr, uint64_t pool)
{
	cvmx_fpa_iobdma_data_t data;

	/*
	 * Hardware only uses 64 bit alligned locations, so convert
	 * from byte address to 64-bit index
	 */
	data.s.scraddr = scr_addr >> 3;
	data.s.len = 1;
	data.s.did = CVMX_FULL_DID(CVMX_OCT_DID_FPA, pool);
	data.s.addr = 0;
	cvmx_send_single(data.u64);
}