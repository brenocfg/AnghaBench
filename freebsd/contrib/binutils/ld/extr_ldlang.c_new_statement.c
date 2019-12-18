#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; int /*<<< orphan*/ * next; } ;
struct TYPE_7__ {TYPE_1__ header; } ;
typedef  TYPE_2__ lang_statement_union_type ;
typedef  int /*<<< orphan*/  lang_statement_list_type ;
typedef  enum statement_enum { ____Placeholder_statement_enum } statement_enum ;

/* Variables and functions */
 int /*<<< orphan*/  lang_statement_append (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **) ; 
 TYPE_2__* stat_alloc (size_t) ; 

__attribute__((used)) static lang_statement_union_type *
new_statement (enum statement_enum type,
	       size_t size,
	       lang_statement_list_type *list)
{
  lang_statement_union_type *new;

  new = stat_alloc (size);
  new->header.type = type;
  new->header.next = NULL;
  lang_statement_append (list, new, &new->header.next);
  return new;
}