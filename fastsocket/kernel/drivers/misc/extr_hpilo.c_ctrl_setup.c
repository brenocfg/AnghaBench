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
struct ccb {void* recv_ctrl; void* send_ctrl; } ;

/* Variables and functions */
 void* ctrl_set (int,int,int) ; 

__attribute__((used)) static void ctrl_setup(struct ccb *ccb, int nr_desc, int l2desc_sz)
{
	/* for simplicity, use the same parameters for send and recv ctrls */
	ccb->send_ctrl = ctrl_set(l2desc_sz, nr_desc-1, nr_desc-1);
	ccb->recv_ctrl = ctrl_set(l2desc_sz, nr_desc-1, nr_desc-1);
}