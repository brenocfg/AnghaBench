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
struct partial_die_info {char* name; scalar_t__ has_children; } ;
struct objfile {int /*<<< orphan*/  global_psymbols; } ;
struct dwarf2_cu {int /*<<< orphan*/  language; struct objfile* objfile; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  LOC_TYPEDEF ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  add_psymbol_to_list (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct objfile*) ; 
 char* alloca (scalar_t__) ; 
 char* scan_partial_symbols (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dwarf2_cu*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *
add_partial_namespace (struct partial_die_info *pdi, char *info_ptr,
		       CORE_ADDR *lowpc, CORE_ADDR *highpc,
		       struct dwarf2_cu *cu, const char *namespace)
{
  struct objfile *objfile = cu->objfile;
  const char *new_name = pdi->name;
  char *full_name;

  /* Calculate the full name of the namespace that we just entered.  */

  if (new_name == NULL)
    new_name = "(anonymous namespace)";
  full_name = alloca (strlen (namespace) + 2 + strlen (new_name) + 1);
  strcpy (full_name, namespace);
  if (*namespace != '\0')
    strcat (full_name, "::");
  strcat (full_name, new_name);

  /* FIXME: carlton/2003-10-07: We can't just replace this by a call
     to add_partial_symbol, because we don't have a way to pass in the
     full name to that function; that might be a flaw in
     add_partial_symbol's interface.  */

  add_psymbol_to_list (full_name, strlen (full_name),
		       VAR_DOMAIN, LOC_TYPEDEF,
		       &objfile->global_psymbols,
		       0, 0, cu->language, objfile);

  /* Now scan partial symbols in that namespace.  */

  if (pdi->has_children)
    info_ptr = scan_partial_symbols (info_ptr, lowpc, highpc, cu, full_name);

  return info_ptr;
}