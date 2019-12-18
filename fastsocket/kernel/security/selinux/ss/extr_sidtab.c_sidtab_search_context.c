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
typedef  int /*<<< orphan*/  u32 ;
struct sidtab_node {struct sidtab_node* next; int /*<<< orphan*/  sid; int /*<<< orphan*/  context; } ;
struct sidtab {struct sidtab_node** htable; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int SIDTAB_SIZE ; 
 scalar_t__ context_cmp (int /*<<< orphan*/ *,struct context*) ; 

__attribute__((used)) static inline u32 sidtab_search_context(struct sidtab *s,
						  struct context *context)
{
	int i;
	struct sidtab_node *cur;

	for (i = 0; i < SIDTAB_SIZE; i++) {
		cur = s->htable[i];
		while (cur) {
			if (context_cmp(&cur->context, context))
				return cur->sid;
			cur = cur->next;
		}
	}
	return 0;
}