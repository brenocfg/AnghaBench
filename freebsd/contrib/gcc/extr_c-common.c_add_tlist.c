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
typedef  scalar_t__ tree ;
struct tlist {scalar_t__ writer; int /*<<< orphan*/  expr; struct tlist* next; } ;

/* Variables and functions */
 struct tlist* new_tlist (struct tlist*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
add_tlist (struct tlist **to, struct tlist *add, tree exclude_writer, int copy)
{
  while (add)
    {
      struct tlist *next = add->next;
      if (!copy)
	add->next = *to;
      if (!exclude_writer || add->writer != exclude_writer)
	*to = copy ? new_tlist (*to, add->expr, add->writer) : add;
      add = next;
    }
}