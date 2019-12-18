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
struct symtab {char* filename; char* dirname; int primary; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKVECTOR (struct symtab*) ; 
 int /*<<< orphan*/  LINETABLE (struct symtab*) ; 
 int /*<<< orphan*/  debug_print_blocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_print_lines (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct symtab*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
debug_print_symtab (struct symtab *s)
{
  fprintf (stderr, "Symtab %p\n    File: %s; Dir: %s\n", s,
	   s->filename, s->dirname);
  fprintf (stderr, "    Blockvector: %p, Primary: %d\n",
	   BLOCKVECTOR (s), s->primary);
  debug_print_blocks (BLOCKVECTOR (s));
  fprintf (stderr, "    Line table: %p\n", LINETABLE (s));
  debug_print_lines (LINETABLE (s));
}