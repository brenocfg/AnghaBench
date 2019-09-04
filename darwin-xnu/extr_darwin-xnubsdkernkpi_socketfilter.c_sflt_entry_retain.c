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
struct socket_filter_entry {int /*<<< orphan*/  sfe_refcount; } ;

/* Variables and functions */
 scalar_t__ OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
sflt_entry_retain(struct socket_filter_entry *entry)
{
	if (OSIncrementAtomic(&entry->sfe_refcount) <= 0) {
		panic("sflt_entry_retain - sfe_refcount <= 0\n");
		/* NOTREACHED */
	}
}