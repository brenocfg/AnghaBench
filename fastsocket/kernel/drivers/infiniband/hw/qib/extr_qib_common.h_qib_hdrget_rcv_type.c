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
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int QLOGIC_IB_RHF_RCVTYPE_MASK ; 
 int QLOGIC_IB_RHF_RCVTYPE_SHIFT ; 
 int __le32_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline __u32 qib_hdrget_rcv_type(const __le32 *rbuf)
{
	return (__le32_to_cpu(rbuf[0]) >> QLOGIC_IB_RHF_RCVTYPE_SHIFT) &
		QLOGIC_IB_RHF_RCVTYPE_MASK;
}