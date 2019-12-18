#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* next; } ;
struct TYPE_6__ {TYPE_1__ header; } ;
typedef  TYPE_2__ lang_statement_union_type ;
typedef  int /*<<< orphan*/  lang_output_section_statement_type ;

/* Variables and functions */
 int /*<<< orphan*/  print_statement (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_statement_list (lang_statement_union_type *s,
		      lang_output_section_statement_type *os)
{
  while (s != NULL)
    {
      print_statement (s, os);
      s = s->header.next;
    }
}