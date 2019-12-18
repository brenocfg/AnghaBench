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
 scalar_t__ IXP_UENGINE_CSR_VIRT_BASE ; 

__attribute__((used)) static void *ixp2000_uengine_csr_area(int uengine)
{
	return ((void *)IXP_UENGINE_CSR_VIRT_BASE) + (uengine << 10);
}