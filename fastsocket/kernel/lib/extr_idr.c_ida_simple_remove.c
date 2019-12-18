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
struct ida {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ida_remove (struct ida*,unsigned int) ; 
 int /*<<< orphan*/  simple_ida_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ida_simple_remove(struct ida *ida, unsigned int id)
{
	BUG_ON((int)id < 0);
	spin_lock(&simple_ida_lock);
	ida_remove(ida, id);
	spin_unlock(&simple_ida_lock);
}