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
struct symtab_and_line {int line; TYPE_1__* symtab; } ;
struct TYPE_2__ {char* filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static char *
extended_canonical_line_spec (struct symtab_and_line sal, const char *name)
{
  char *r;

  if (sal.symtab == NULL || sal.symtab->filename == NULL || sal.line <= 0)
    return NULL;

  r = (char *) xmalloc (strlen (name) + strlen (sal.symtab->filename)
			+ sizeof (sal.line) * 3 + 3);
  sprintf (r, "%s:'%s':%d", sal.symtab->filename, name, sal.line);
  return r;
}