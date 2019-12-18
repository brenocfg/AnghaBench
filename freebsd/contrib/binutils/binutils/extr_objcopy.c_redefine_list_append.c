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
struct redefine_node {struct redefine_node* next; void* target; void* source; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*,char const*) ; 
 struct redefine_node* redefine_sym_list ; 
 scalar_t__ strcmp (char const*,void*) ; 
 void* strdup (char const*) ; 
 struct redefine_node* xmalloc (int) ; 

__attribute__((used)) static void
redefine_list_append (const char *cause, const char *source, const char *target)
{
  struct redefine_node **p;
  struct redefine_node *list;
  struct redefine_node *new_node;

  for (p = &redefine_sym_list; (list = *p) != NULL; p = &list->next)
    {
      if (strcmp (source, list->source) == 0)
	fatal (_("%s: Multiple redefinition of symbol \"%s\""),
	       cause, source);

      if (strcmp (target, list->target) == 0)
	fatal (_("%s: Symbol \"%s\" is target of more than one redefinition"),
	       cause, target);
    }

  new_node = xmalloc (sizeof (struct redefine_node));

  new_node->source = strdup (source);
  new_node->target = strdup (target);
  new_node->next = NULL;

  *p = new_node;
}