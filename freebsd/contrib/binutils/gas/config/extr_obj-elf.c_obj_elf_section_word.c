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
 int SHF_ALLOC ; 
 int SHF_EXECINSTR ; 
 int SHF_TLS ; 
 int SHF_WRITE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int md_elf_section_word (char*,size_t) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
obj_elf_section_word (char *str, size_t len)
{
  if (len == 5 && strncmp (str, "write", 5) == 0)
    return SHF_WRITE;
  if (len == 5 && strncmp (str, "alloc", 5) == 0)
    return SHF_ALLOC;
  if (len == 9 && strncmp (str, "execinstr", 9) == 0)
    return SHF_EXECINSTR;
  if (len == 3 && strncmp (str, "tls", 3) == 0)
    return SHF_TLS;

#ifdef md_elf_section_word
  {
    int md_attr = md_elf_section_word (str, len);
    if (md_attr >= 0)
      return md_attr;
  }
#endif

  as_warn (_("unrecognized section attribute"));
  return 0;
}