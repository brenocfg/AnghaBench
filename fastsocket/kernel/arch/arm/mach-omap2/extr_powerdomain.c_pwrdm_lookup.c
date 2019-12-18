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
struct powerdomain {int dummy; } ;

/* Variables and functions */
 struct powerdomain* _pwrdm_lookup (char const*) ; 
 int /*<<< orphan*/  pwrdm_rwlock ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct powerdomain *pwrdm_lookup(const char *name)
{
	struct powerdomain *pwrdm;
	unsigned long flags;

	if (!name)
		return NULL;

	read_lock_irqsave(&pwrdm_rwlock, flags);
	pwrdm = _pwrdm_lookup(name);
	read_unlock_irqrestore(&pwrdm_rwlock, flags);

	return pwrdm;
}