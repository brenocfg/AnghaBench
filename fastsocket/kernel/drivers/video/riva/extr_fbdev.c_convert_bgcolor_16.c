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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline void convert_bgcolor_16(u32 *col)
{
	*col = ((*col & 0x0000F800) << 8)
		| ((*col & 0x00007E0) << 5)
		| ((*col & 0x0000001F) << 3)
		|	   0xFF000000;
	mb();
}