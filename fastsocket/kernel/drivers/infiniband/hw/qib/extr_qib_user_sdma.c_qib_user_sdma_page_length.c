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
 unsigned long PAGE_MASK ; 
 unsigned long const PAGE_SIZE ; 

__attribute__((used)) static int qib_user_sdma_page_length(unsigned long addr, unsigned long len)
{
	const unsigned long offset = addr & ~PAGE_MASK;

	return ((offset + len) > PAGE_SIZE) ? (PAGE_SIZE - offset) : len;
}