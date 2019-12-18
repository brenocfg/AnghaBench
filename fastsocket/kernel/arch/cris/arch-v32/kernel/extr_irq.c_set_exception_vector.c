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
typedef  scalar_t__ irqvectptr ;
struct TYPE_2__ {scalar_t__* v; } ;

/* Variables and functions */
 TYPE_1__* etrax_irv ; 

void
set_exception_vector(int n, irqvectptr addr)
{
	etrax_irv->v[n] = (irqvectptr) addr;
}