#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* next; } ;
struct TYPE_8__ {TYPE_1__ header; } ;
typedef  TYPE_2__ lang_statement_union_type ;
struct TYPE_9__ {int /*<<< orphan*/ * map_file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  abs_output_section ; 
 TYPE_6__ config ; 
 int /*<<< orphan*/  print_statement (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_statement_list (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stderr ; 

void
dprint_statement (lang_statement_union_type *s, int n)
{
  FILE *map_save = config.map_file;

  config.map_file = stderr;

  if (n < 0)
    print_statement_list (s, abs_output_section);
  else
    {
      while (s && --n >= 0)
	{
	  print_statement (s, abs_output_section);
	  s = s->header.next;
	}
    }

  config.map_file = map_save;
}