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
struct bfd_elf_version_expr {char const* pattern; char const* symbol; void* mask; scalar_t__ script; scalar_t__ symver; struct bfd_elf_version_expr* next; } ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 void* BFD_ELF_VERSION_CXX_TYPE ; 
 void* BFD_ELF_VERSION_C_TYPE ; 
 void* BFD_ELF_VERSION_JAVA_TYPE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,char const*) ; 
 struct bfd_elf_version_expr* ldemul_new_vers_pattern (struct bfd_elf_version_expr*) ; 
 char const* realsymbol (char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 struct bfd_elf_version_expr* xmalloc (int) ; 

struct bfd_elf_version_expr *
lang_new_vers_pattern (struct bfd_elf_version_expr *orig,
		       const char *new,
		       const char *lang,
		       bfd_boolean literal_p)
{
  struct bfd_elf_version_expr *ret;

  ret = xmalloc (sizeof *ret);
  ret->next = orig;
  ret->pattern = literal_p ? NULL : new;
  ret->symver = 0;
  ret->script = 0;
  ret->symbol = literal_p ? new : realsymbol (new);

  if (lang == NULL || strcasecmp (lang, "C") == 0)
    ret->mask = BFD_ELF_VERSION_C_TYPE;
  else if (strcasecmp (lang, "C++") == 0)
    ret->mask = BFD_ELF_VERSION_CXX_TYPE;
  else if (strcasecmp (lang, "Java") == 0)
    ret->mask = BFD_ELF_VERSION_JAVA_TYPE;
  else
    {
      einfo (_("%X%P: unknown language `%s' in version information\n"),
	     lang);
      ret->mask = BFD_ELF_VERSION_C_TYPE;
    }

  return ldemul_new_vers_pattern (ret);
}