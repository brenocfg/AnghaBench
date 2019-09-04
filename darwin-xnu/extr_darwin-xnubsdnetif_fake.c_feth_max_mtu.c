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
 int ETHER_HDR_LEN ; 
 int M16KCLBYTES ; 
 int MBIGCLBYTES ; 
 scalar_t__ njcl ; 

__attribute__((used)) static inline int
feth_max_mtu(void)
{
	if (njcl > 0) {
		return (M16KCLBYTES - ETHER_HDR_LEN);
	}
	return (MBIGCLBYTES - ETHER_HDR_LEN);
}