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
struct selector {int /*<<< orphan*/  invalid_paths; } ;
struct path_selector {scalar_t__ context; } ;
struct path_info {int /*<<< orphan*/  list; } ;
struct dm_path {struct path_info* pscontext; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rr_fail_path(struct path_selector *ps, struct dm_path *p)
{
	struct selector *s = (struct selector *) ps->context;
	struct path_info *pi = p->pscontext;

	list_move(&pi->list, &s->invalid_paths);
}