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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_run_gc (int /*<<< orphan*/ ,struct net*,int) ; 

__attribute__((used)) static void fib6_gc_timer_cb(unsigned long arg)
{
	fib6_run_gc(0, (struct net *)arg, true);
}