#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* segT ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  as_where (char**,unsigned int*) ; 
 char* frag_more (int) ; 
 unsigned int get_stab_string_offset (char*,char*) ; 
 int /*<<< orphan*/  know (int) ; 
 int /*<<< orphan*/  md_number_to_chars (char*,unsigned int,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 char* xmalloc (scalar_t__) ; 

void
obj_coff_init_stab_section (segT seg)
{
  char *file;
  char *p;
  char *stabstr_name;
  unsigned int stroff;

  /* Make space for this first symbol.  */
  p = frag_more (12);
  /* Zero it out.  */
  memset (p, 0, 12);
  as_where (&file, (unsigned int *) NULL);
  stabstr_name = xmalloc (strlen (seg->name) + 4);
  strcpy (stabstr_name, seg->name);
  strcat (stabstr_name, "str");
  stroff = get_stab_string_offset (file, stabstr_name);
  know (stroff == 1);
  md_number_to_chars (p, stroff, 4);
}