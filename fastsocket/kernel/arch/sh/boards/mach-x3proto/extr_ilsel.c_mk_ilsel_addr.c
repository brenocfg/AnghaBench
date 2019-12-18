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
 unsigned long ILSEL_BASE ; 
 int ilsel_offset (unsigned int) ; 

__attribute__((used)) static inline unsigned long mk_ilsel_addr(unsigned int bit)
{
	return ILSEL_BASE + ((ilsel_offset(bit) >> 1) & ~0x1);
}