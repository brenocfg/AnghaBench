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
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_dump_index { ____Placeholder_tree_dump_index } tree_dump_index ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * dump_begin (int,int*) ; 
 int /*<<< orphan*/  dump_end (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_function_to_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
dump_function (enum tree_dump_index phase, tree fn)
{
  FILE *stream;
  int flags;

  stream = dump_begin (phase, &flags);
  if (stream)
    {
      dump_function_to_file (fn, stream, flags);
      dump_end (phase, stream);
    }
}