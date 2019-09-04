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
struct TYPE_2__ {scalar_t__ threads_minus_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wait (int volatile*,int volatile*,int,int) ; 
 scalar_t__ a_swap (int volatile*,int) ; 
 TYPE_1__ libc ; 

void __lock(volatile int *l)
{
	if (libc.threads_minus_1)
		while (a_swap(l, 1)) __wait(l, l+1, 1, 1);
}