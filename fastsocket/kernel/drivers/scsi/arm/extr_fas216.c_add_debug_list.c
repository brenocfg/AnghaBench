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
struct TYPE_2__ {int stat; int ssr; int isr; int ph; } ;

/* Variables and functions */
 int PH_SIZE ; 
 TYPE_1__* ph_list ; 
 size_t ph_ptr ; 

__attribute__((used)) static void add_debug_list(int stat, int ssr, int isr, int ph)
{
	ph_list[ph_ptr].stat = stat;
	ph_list[ph_ptr].ssr = ssr;
	ph_list[ph_ptr].isr = isr;
	ph_list[ph_ptr].ph = ph;

	ph_ptr = (ph_ptr + 1) & (PH_SIZE-1);
}