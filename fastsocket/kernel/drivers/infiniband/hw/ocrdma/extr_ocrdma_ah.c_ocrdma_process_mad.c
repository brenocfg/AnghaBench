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
struct ib_wc {int dummy; } ;
struct ib_mad {int dummy; } ;
struct ib_grh {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_MAD_RESULT_SUCCESS ; 

int ocrdma_process_mad(struct ib_device *ibdev,
		       int process_mad_flags,
		       u8 port_num,
		       struct ib_wc *in_wc,
		       struct ib_grh *in_grh,
		       struct ib_mad *in_mad, struct ib_mad *out_mad)
{
	return IB_MAD_RESULT_SUCCESS;
}