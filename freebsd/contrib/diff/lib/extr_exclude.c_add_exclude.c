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
struct patopts {char const* pattern; int options; } ;
struct exclude {scalar_t__ exclude_count; scalar_t__ exclude_alloc; struct patopts* exclude; } ;

/* Variables and functions */
 struct patopts* x2nrealloc (struct patopts*,scalar_t__*,int) ; 

void
add_exclude (struct exclude *ex, char const *pattern, int options)
{
  struct patopts *patopts;

  if (ex->exclude_count == ex->exclude_alloc)
    ex->exclude = x2nrealloc (ex->exclude, &ex->exclude_alloc,
			      sizeof *ex->exclude);

  patopts = &ex->exclude[ex->exclude_count++];
  patopts->pattern = pattern;
  patopts->options = options;
}