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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int) ; 

__attribute__((used)) static inline void print_time(char *s)
{
#ifdef DEBUG_TIMING
	struct timeval tv;
	do_gettimeofday(&tv);
	printk("%s: %d.%d\n", s, (int)tv.tv_sec, (int)tv.tv_usec);
#endif
}