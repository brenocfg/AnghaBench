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
struct link {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  blocked; } ;
struct bearer {int /*<<< orphan*/  cong_links; TYPE_1__ publ; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_bearer_resolve_congestion (struct bearer*,struct link*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int tipc_bearer_congested(struct bearer *b_ptr, struct link *l_ptr)
{
	if (unlikely(b_ptr->publ.blocked))
		return 1;
	if (likely(list_empty(&b_ptr->cong_links)))
		return 0;
	return !tipc_bearer_resolve_congestion(b_ptr, l_ptr);
}