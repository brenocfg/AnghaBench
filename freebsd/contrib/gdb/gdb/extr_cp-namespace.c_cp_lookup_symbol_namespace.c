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
struct using_direct {char* inner; int /*<<< orphan*/  outer; struct using_direct* next; } ;
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  domain_enum ;

/* Variables and functions */
 char* alloca (scalar_t__) ; 
 struct using_direct* block_using (struct block const*) ; 
 int /*<<< orphan*/  cp_is_anonymous (char const*) ; 
 struct symbol* lookup_symbol_file (char const*,char const*,struct block const*,int /*<<< orphan*/  const,struct symtab**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

struct symbol *
cp_lookup_symbol_namespace (const char *namespace,
			    const char *name,
			    const char *linkage_name,
			    const struct block *block,
			    const domain_enum domain,
			    struct symtab **symtab)
{
  const struct using_direct *current;
  struct symbol *sym;

  /* First, go through the using directives.  If any of them add new
     names to the namespace we're searching in, see if we can find a
     match by applying them.  */

  for (current = block_using (block);
       current != NULL;
       current = current->next)
    {
      if (strcmp (namespace, current->outer) == 0)
	{
	  sym = cp_lookup_symbol_namespace (current->inner,
					    name,
					    linkage_name,
					    block,
					    domain,
					    symtab);
	  if (sym != NULL)
	    return sym;
	}
    }

  /* We didn't find anything by applying any of the using directives
     that are still applicable; so let's see if we've got a match
     using the current namespace.  */
  
  if (namespace[0] == '\0')
    {
      return lookup_symbol_file (name, linkage_name, block,
				 domain, symtab, 0);
    }
  else
    {
      char *concatenated_name
	= alloca (strlen (namespace) + 2 + strlen (name) + 1);
      strcpy (concatenated_name, namespace);
      strcat (concatenated_name, "::");
      strcat (concatenated_name, name);
      sym = lookup_symbol_file (concatenated_name, linkage_name,
				block, domain, symtab,
				cp_is_anonymous (namespace));
      return sym;
    }
}