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
 scalar_t__ PCNET32_DWIO_RESET ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 

__attribute__((used)) static void pcnet32_dwio_reset(unsigned long addr)
{
	inl(addr + PCNET32_DWIO_RESET);
}