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
struct bfd_elf_version_expr {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  lang_append_dynamic_list (struct bfd_elf_version_expr*) ; 
 struct bfd_elf_version_expr* lang_new_vers_pattern (struct bfd_elf_version_expr*,char const*,char*,int /*<<< orphan*/ ) ; 

void
lang_append_dynamic_list_cpp_typeinfo (void)
{
  const char * symbols [] =
    {
      "typeinfo name for*",
      "typeinfo for*"
    };
  struct bfd_elf_version_expr *dynamic = NULL;
  unsigned int i;

  for (i = 0; i < ARRAY_SIZE (symbols); i++)
    dynamic = lang_new_vers_pattern (dynamic, symbols [i], "C++",
				     FALSE);

  lang_append_dynamic_list (dynamic);
}