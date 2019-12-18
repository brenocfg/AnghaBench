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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int DEBUGT ; 
 TYPE_1__* DP ; 
 scalar_t__ debugtimer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  printk (char*,char const*,scalar_t__) ; 

__attribute__((used)) static inline void debugt(const char *message)
{
	if (DP->flags & DEBUGT)
		printk("%s dtime=%lu\n", message, jiffies - debugtimer);
}