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
 scalar_t__ PCNET32_DWIO_RAP ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static int pcnet32_dwio_check(unsigned long addr)
{
	outl(88, addr + PCNET32_DWIO_RAP);
	return ((inl(addr + PCNET32_DWIO_RAP) & 0xffff) == 88);
}