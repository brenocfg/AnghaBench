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
 int INFINIPATH_RHF_L_USE_EGR ; 
 int __le32_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline __u32 ipath_hdrget_use_egr_buf(const __le32 *rbuf)
{
	return __le32_to_cpu(rbuf[0]) & INFINIPATH_RHF_L_USE_EGR;
}