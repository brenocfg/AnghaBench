#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ ldlang_undef_chain_list_type ;

/* Variables and functions */
 int /*<<< orphan*/  insert_undefined (int /*<<< orphan*/ ) ; 
 TYPE_1__* ldlang_undef_chain_list_head ; 
 int /*<<< orphan*/ * output_bfd ; 
 TYPE_1__* stat_alloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const* const) ; 

void
ldlang_add_undef (const char *const name)
{
  ldlang_undef_chain_list_type *new =
    stat_alloc (sizeof (ldlang_undef_chain_list_type));

  new->next = ldlang_undef_chain_list_head;
  ldlang_undef_chain_list_head = new;

  new->name = xstrdup (name);

  if (output_bfd != NULL)
    insert_undefined (new->name);
}