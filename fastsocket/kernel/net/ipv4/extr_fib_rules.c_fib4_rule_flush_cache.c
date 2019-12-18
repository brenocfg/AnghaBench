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
struct fib_rules_ops {int /*<<< orphan*/  fro_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt_cache_flush (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fib4_rule_flush_cache(struct fib_rules_ops *ops)
{
	rt_cache_flush(ops->fro_net, -1);
}