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
struct unw_script {unsigned long ip; unsigned long pr_val; unsigned long pr_mask; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline long
cache_match (struct unw_script *script, unsigned long ip, unsigned long pr)
{
	read_lock(&script->lock);
	if (ip == script->ip && ((pr ^ script->pr_val) & script->pr_mask) == 0)
		/* keep the read lock... */
		return 1;
	read_unlock(&script->lock);
	return 0;
}