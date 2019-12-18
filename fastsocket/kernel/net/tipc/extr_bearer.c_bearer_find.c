#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct bearer {TYPE_1__ publ; scalar_t__ active; } ;

/* Variables and functions */
 scalar_t__ MAX_BEARERS ; 
 scalar_t__ TIPC_NET_MODE ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct bearer* tipc_bearers ; 
 scalar_t__ tipc_mode ; 

__attribute__((used)) static struct bearer *bearer_find(const char *name)
{
	struct bearer *b_ptr;
	u32 i;

	if (tipc_mode != TIPC_NET_MODE)
		return NULL;

	for (i = 0, b_ptr = tipc_bearers; i < MAX_BEARERS; i++, b_ptr++) {
		if (b_ptr->active && (!strcmp(b_ptr->publ.name, name)))
			return b_ptr;
	}
	return NULL;
}