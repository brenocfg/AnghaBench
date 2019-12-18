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
struct TYPE_2__ {int flags; int personality; } ;

/* Variables and functions */
 int ADDR_NO_RANDOMIZE ; 
 int PF_RANDOMIZE ; 
 TYPE_1__* current ; 

__attribute__((used)) static bool should_randomize(void)
{
	return (current->flags & PF_RANDOMIZE) &&
		!(current->personality & ADDR_NO_RANDOMIZE);
}