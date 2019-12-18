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
struct ehca_mw {int /*<<< orphan*/  mwlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ehca_gen_err (char*) ; 
 struct ehca_mw* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mw_cache ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ehca_mw *ehca_mw_new(void)
{
	struct ehca_mw *me;

	me = kmem_cache_zalloc(mw_cache, GFP_KERNEL);
	if (me)
		spin_lock_init(&me->mwlock);
	else
		ehca_gen_err("alloc failed");

	return me;
}