#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lang_output_section_phdr_list ;
typedef  int /*<<< orphan*/  fill_type ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MEMORY_REGION ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISALNUM (char const) ; 
 int /*<<< orphan*/  LOADADDR ; 
 int /*<<< orphan*/  SIZEOF ; 
 TYPE_1__* current_section ; 
 int /*<<< orphan*/  exp_binop (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exp_nameop (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  exp_provide (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lang_add_assignment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lang_leave_output_section_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char const*) ; 
 char* xmalloc (int) ; 

void
lang_leave_overlay_section (fill_type *fill,
			    lang_output_section_phdr_list *phdrs)
{
  const char *name;
  char *clean, *s2;
  const char *s1;
  char *buf;

  name = current_section->name;

  /* For now, assume that DEFAULT_MEMORY_REGION is the run-time memory
     region and that no load-time region has been specified.  It doesn't
     really matter what we say here, since lang_leave_overlay will
     override it.  */
  lang_leave_output_section_statement (fill, DEFAULT_MEMORY_REGION, phdrs, 0);

  /* Define the magic symbols.  */

  clean = xmalloc (strlen (name) + 1);
  s2 = clean;
  for (s1 = name; *s1 != '\0'; s1++)
    if (ISALNUM (*s1) || *s1 == '_')
      *s2++ = *s1;
  *s2 = '\0';

  buf = xmalloc (strlen (clean) + sizeof "__load_start_");
  sprintf (buf, "__load_start_%s", clean);
  lang_add_assignment (exp_provide (buf,
				    exp_nameop (LOADADDR, name),
				    FALSE));

  buf = xmalloc (strlen (clean) + sizeof "__load_stop_");
  sprintf (buf, "__load_stop_%s", clean);
  lang_add_assignment (exp_provide (buf,
				    exp_binop ('+',
					       exp_nameop (LOADADDR, name),
					       exp_nameop (SIZEOF, name)),
				    FALSE));

  free (clean);
}