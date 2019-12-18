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
struct tlist {scalar_t__ writer; int /*<<< orphan*/  expr; struct tlist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  warn_for_collisions_1 (int /*<<< orphan*/ ,scalar_t__,struct tlist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
warn_for_collisions (struct tlist *list)
{
  struct tlist *tmp;

  for (tmp = list; tmp; tmp = tmp->next)
    {
      if (tmp->writer)
	warn_for_collisions_1 (tmp->expr, tmp->writer, list, 0);
    }
}