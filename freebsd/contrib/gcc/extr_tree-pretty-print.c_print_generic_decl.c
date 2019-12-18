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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  maybe_init_pretty_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_write_text_to_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_declaration (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

void
print_generic_decl (FILE *file, tree decl, int flags)
{
  maybe_init_pretty_print (file);
  print_declaration (&buffer, decl, 2, flags);
  pp_write_text_to_stream (&buffer);
}