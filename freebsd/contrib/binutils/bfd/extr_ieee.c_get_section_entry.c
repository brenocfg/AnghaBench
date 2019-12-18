#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int section_table_size; TYPE_2__** section_table; } ;
typedef  TYPE_1__ ieee_data_type ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_9__ {unsigned int target_index; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 char* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* bfd_make_section (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__** bfd_realloc (TYPE_2__**,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static asection *
get_section_entry (bfd *abfd, ieee_data_type *ieee, unsigned int index)
{
  if (index >= ieee->section_table_size)
    {
      unsigned int c, i;
      asection **n;
      bfd_size_type amt;

      c = ieee->section_table_size;
      if (c == 0)
	c = 20;
      while (c <= index)
	c *= 2;

      amt = c;
      amt *= sizeof (asection *);
      n = bfd_realloc (ieee->section_table, amt);
      if (n == NULL)
	return NULL;

      for (i = ieee->section_table_size; i < c; i++)
	n[i] = NULL;

      ieee->section_table = n;
      ieee->section_table_size = c;
    }

  if (ieee->section_table[index] == (asection *) NULL)
    {
      char *tmp = bfd_alloc (abfd, (bfd_size_type) 11);
      asection *section;

      if (!tmp)
	return NULL;
      sprintf (tmp, " fsec%4d", index);
      section = bfd_make_section (abfd, tmp);
      ieee->section_table[index] = section;
      section->target_index = index;
      ieee->section_table[index] = section;
    }
  return ieee->section_table[index];
}