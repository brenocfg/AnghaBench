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
struct rxrpc_local {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SLAB_OKAY (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char const*) ; 

__attribute__((used)) static inline void __rxrpc_get_local(struct rxrpc_local *local, const char *f)
{
	CHECK_SLAB_OKAY(&local->usage);
	if (atomic_inc_return(&local->usage) == 1)
		printk("resurrected (%s)\n", f);
}