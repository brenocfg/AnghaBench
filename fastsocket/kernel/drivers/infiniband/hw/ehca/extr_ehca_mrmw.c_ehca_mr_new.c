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
struct ehca_mr {int /*<<< orphan*/  mrlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ehca_gen_err (char*) ; 
 struct ehca_mr* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mr_cache ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ehca_mr *ehca_mr_new(void)
{
	struct ehca_mr *me;

	me = kmem_cache_zalloc(mr_cache, GFP_KERNEL);
	if (me)
		spin_lock_init(&me->mrlock);
	else
		ehca_gen_err("alloc failed");

	return me;
}