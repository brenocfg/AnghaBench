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
 scalar_t__ DATA_REG_LOW ; 
 scalar_t__ INDEX_REG ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

__attribute__((used)) static inline void nsp32_index_write2(unsigned int   base,
				      unsigned int   reg,
				      unsigned short val)
{
	outb(reg, base + INDEX_REG   );
	outw(val, base + DATA_REG_LOW);
}