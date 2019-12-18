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
struct target_notify {int dummy; } ;

/* Variables and functions */
 struct target_notify* SLIST_NEXT (struct target_notify*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tn ; 

struct target_notify *
target_next_notify(struct target_notify *notify)
{
	if (notify == NULL)
		return (NULL);

	return (SLIST_NEXT(notify, tn));
}