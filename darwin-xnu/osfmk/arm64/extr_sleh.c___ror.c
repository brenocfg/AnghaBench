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
 int CHAR_BIT ; 

__attribute__((used)) static inline unsigned
__ror(unsigned value, unsigned shift)
{
	return (((unsigned)(value) >> (unsigned)(shift)) |
	        (unsigned)(value) << ((unsigned)(sizeof(unsigned) * CHAR_BIT) - (unsigned)(shift)));
}