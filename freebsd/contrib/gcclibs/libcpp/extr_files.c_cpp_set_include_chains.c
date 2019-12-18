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
struct TYPE_6__ {int quote_ignores_source_dir; TYPE_2__* bracket_include; TYPE_2__* quote_include; } ;
typedef  TYPE_1__ cpp_reader ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; int /*<<< orphan*/ * name_map; struct TYPE_7__* next; } ;
typedef  TYPE_2__ cpp_dir ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void
cpp_set_include_chains (cpp_reader *pfile, cpp_dir *quote, cpp_dir *bracket,
			int quote_ignores_source_dir)
{
  pfile->quote_include = quote;
  pfile->bracket_include = quote;
  pfile->quote_ignores_source_dir = quote_ignores_source_dir;

  for (; quote; quote = quote->next)
    {
      quote->name_map = NULL;
      quote->len = strlen (quote->name);
      if (quote == bracket)
	pfile->bracket_include = bracket;
    }
}