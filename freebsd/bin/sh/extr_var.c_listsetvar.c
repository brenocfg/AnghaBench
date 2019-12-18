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
struct arglist {int count; int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  savestr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setvareq (int /*<<< orphan*/ ,int) ; 

void
listsetvar(struct arglist *list, int flags)
{
	int i;

	INTOFF;
	for (i = 0; i < list->count; i++)
		setvareq(savestr(list->args[i]), flags);
	INTON;
}