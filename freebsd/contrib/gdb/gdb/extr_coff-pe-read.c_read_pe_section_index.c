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

/* Variables and functions */
 int PE_SECTION_INDEX_BSS ; 
 int PE_SECTION_INDEX_DATA ; 
 int PE_SECTION_INDEX_INVALID ; 
 int PE_SECTION_INDEX_TEXT ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
read_pe_section_index (const char *section_name)
{
  if (strcmp (section_name, ".text") == 0)
    {
      return PE_SECTION_INDEX_TEXT;
    }

  else if (strcmp (section_name, ".data") == 0)
    {
      return PE_SECTION_INDEX_DATA;
    }

  else if (strcmp (section_name, ".bss") == 0)
    {
      return PE_SECTION_INDEX_BSS;
    }

  else
    {
      return PE_SECTION_INDEX_INVALID;
    }
}