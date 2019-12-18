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
struct compact_control {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int compact_checklock_irqsave (int /*<<< orphan*/ *,unsigned long*,int,struct compact_control*) ; 

__attribute__((used)) static inline bool compact_trylock_irqsave(spinlock_t *lock,
			unsigned long *flags, struct compact_control *cc)
{
	return compact_checklock_irqsave(lock, flags, false, cc);
}