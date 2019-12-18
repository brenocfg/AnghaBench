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
struct api_info {int dummy; } ;

/* Variables and functions */
 struct api_info* __get_info (unsigned long) ; 
 int /*<<< orphan*/  __put_ref (struct api_info*) ; 
 int /*<<< orphan*/  hvapi_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void sun4v_hvapi_unregister(unsigned long group)
{
	struct api_info *p;
	unsigned long flags;

	spin_lock_irqsave(&hvapi_lock, flags);
	p = __get_info(group);
	if (p)
		__put_ref(p);
	spin_unlock_irqrestore(&hvapi_lock, flags);
}