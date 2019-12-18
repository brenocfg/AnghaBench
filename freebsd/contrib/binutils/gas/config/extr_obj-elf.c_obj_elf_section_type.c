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
 int SHT_FINI_ARRAY ; 
 int SHT_INIT_ARRAY ; 
 int SHT_NOBITS ; 
 int SHT_NOTE ; 
 int SHT_PREINIT_ARRAY ; 
 int SHT_PROGBITS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int md_elf_section_type (char*,size_t) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
obj_elf_section_type (char *str, size_t len)
{
  if (len == 8 && strncmp (str, "progbits", 8) == 0)
    return SHT_PROGBITS;
  if (len == 6 && strncmp (str, "nobits", 6) == 0)
    return SHT_NOBITS;
  if (len == 4 && strncmp (str, "note", 4) == 0)
    return SHT_NOTE;
  if (len == 10 && strncmp (str, "init_array", 10) == 0)
    return SHT_INIT_ARRAY;
  if (len == 10 && strncmp (str, "fini_array", 10) == 0)
    return SHT_FINI_ARRAY;
  if (len == 13 && strncmp (str, "preinit_array", 13) == 0)
    return SHT_PREINIT_ARRAY;

#ifdef md_elf_section_type
  {
    int md_type = md_elf_section_type (str, len);
    if (md_type >= 0)
      return md_type;
  }
#endif

  as_warn (_("unrecognized section type"));
  return 0;
}