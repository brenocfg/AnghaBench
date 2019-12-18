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
 int INFINIPATH_I_VERS_MASK ; 
 int INFINIPATH_I_VERS_SHIFT ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __u32 ipath_hdrget_ipath_ver(__le32 hdrword)
{
	return (__le32_to_cpu(hdrword) >> INFINIPATH_I_VERS_SHIFT)
	    & INFINIPATH_I_VERS_MASK;
}