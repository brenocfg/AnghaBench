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
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ PCNET32_DWIO_BDP ; 
 scalar_t__ PCNET32_DWIO_RAP ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void pcnet32_dwio_write_bcr(unsigned long addr, int index, u16 val)
{
	outl(index, addr + PCNET32_DWIO_RAP);
	outl(val, addr + PCNET32_DWIO_BDP);
}