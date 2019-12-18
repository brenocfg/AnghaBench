#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cmd_list_element {struct cmd_list_element* next; TYPE_2__* hookee_post; TYPE_1__* hookee_pre; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ hook_post; } ;
struct TYPE_3__ {scalar_t__ hook_pre; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xfree (struct cmd_list_element*) ; 

void
delete_cmd (char *name, struct cmd_list_element **list)
{
  struct cmd_list_element *c;
  struct cmd_list_element *p;

  while (*list && strcmp ((*list)->name, name) == 0)
    {
      if ((*list)->hookee_pre)
      (*list)->hookee_pre->hook_pre = 0;   /* Hook slips out of its mouth */
      if ((*list)->hookee_post)
      (*list)->hookee_post->hook_post = 0; /* Hook slips out of its bottom  */
      p = (*list)->next;
      xfree (* list);
      *list = p;
    }

  if (*list)
    for (c = *list; c->next;)
      {
	if (strcmp (c->next->name, name) == 0)
	  {
          if (c->next->hookee_pre)
            c->next->hookee_pre->hook_pre = 0; /* hooked cmd gets away.  */
          if (c->next->hookee_post)
            c->next->hookee_post->hook_post = 0; /* remove post hook */
                                               /* :( no fishing metaphore */
	    p = c->next->next;
	    xfree (c->next);
	    c->next = p;
	  }
	else
	  c = c->next;
      }
}