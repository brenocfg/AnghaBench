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
struct ap_queue_status {int dummy; } ;
typedef  unsigned long ap_qid_t ;

/* Variables and functions */

__attribute__((used)) static inline struct ap_queue_status
ap_test_queue(ap_qid_t qid, int *queue_depth, int *device_type)
{
	register unsigned long reg0 asm ("0") = qid;
	register struct ap_queue_status reg1 asm ("1");
	register unsigned long reg2 asm ("2") = 0UL;

	asm volatile(".long 0xb2af0000"		/* PQAP(TAPQ) */
		     : "+d" (reg0), "=d" (reg1), "+d" (reg2) : : "cc");
	*device_type = (int) (reg2 >> 24);
	*queue_depth = (int) (reg2 & 0xff);
	return reg1;
}