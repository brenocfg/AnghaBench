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
struct redefine_node {char const* target; int /*<<< orphan*/  source; struct redefine_node* next; } ;

/* Variables and functions */
 struct redefine_node* redefine_sym_list ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
lookup_sym_redefinition (const char *source)
{
  struct redefine_node *list;

  for (list = redefine_sym_list; list != NULL; list = list->next)
    if (strcmp (source, list->source) == 0)
      return list->target;

  return source;
}