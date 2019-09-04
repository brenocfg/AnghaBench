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
struct klist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INIT (struct klist*) ; 

void
klist_init(struct klist *list)
{
	SLIST_INIT(list);
}