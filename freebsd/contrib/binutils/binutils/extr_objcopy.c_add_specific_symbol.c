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
struct symlist {char const* name; struct symlist* next; } ;

/* Variables and functions */
 struct symlist* xmalloc (int) ; 

__attribute__((used)) static void
add_specific_symbol (const char *name, struct symlist **list)
{
  struct symlist *tmp_list;

  tmp_list = xmalloc (sizeof (struct symlist));
  tmp_list->name = name;
  tmp_list->next = *list;
  *list = tmp_list;
}