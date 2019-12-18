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
typedef  int u16 ;
struct TYPE_2__ {int (* r_16 ) (unsigned int) ;} ;

/* Variables and functions */
 TYPE_1__ rw_funcs ; 
 int stub1 (unsigned int) ; 
 int stub2 (unsigned int) ; 

unsigned int  m68k_read_memory_32(unsigned int address)
{
   u16 val1 = rw_funcs.r_16(address);

   return (val1 << 16 | rw_funcs.r_16(address + 2));
}