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
 scalar_t__ IPOIB_UD_BUF_SIZE (unsigned int) ; 
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static inline int ipoib_ud_need_sg(unsigned int ib_mtu)
{
	return IPOIB_UD_BUF_SIZE(ib_mtu) > PAGE_SIZE;
}