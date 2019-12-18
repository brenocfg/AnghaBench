#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* w_8 ) (unsigned int,unsigned int) ;} ;

/* Variables and functions */
 TYPE_1__ rw_funcs ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned int) ; 

void m68k_write_memory_8(unsigned int address, unsigned int value)
{
   rw_funcs.w_8(address, value);
}