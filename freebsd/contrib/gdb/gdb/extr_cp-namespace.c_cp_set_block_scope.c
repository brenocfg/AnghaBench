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
struct symbol {int dummy; } ;
struct obstack {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 char* SYMBOL_CPLUS_DEMANGLED_NAME (struct symbol const*) ; 
 int /*<<< orphan*/  block_set_scope (struct block*,int /*<<< orphan*/ ,struct obstack*) ; 
 unsigned int cp_entire_prefix_len (char const*) ; 
 int /*<<< orphan*/  obsavestring (char const*,unsigned int,struct obstack*) ; 
 char const* processing_current_prefix ; 
 scalar_t__ processing_has_namespace_info ; 
 unsigned int strlen (char const*) ; 

void
cp_set_block_scope (const struct symbol *symbol,
		    struct block *block,
		    struct obstack *obstack)
{
  /* Make sure that the name was originally mangled: if not, there
     certainly isn't any namespace information to worry about!  */

  if (SYMBOL_CPLUS_DEMANGLED_NAME (symbol) != NULL)
    {
      if (processing_has_namespace_info)
	{
	  block_set_scope
	    (block, obsavestring (processing_current_prefix,
				  strlen (processing_current_prefix),
				  obstack),
	     obstack);
	}
      else
	{
	  /* Try to figure out the appropriate namespace from the
	     demangled name.  */

	  /* FIXME: carlton/2003-04-15: If the function in question is
	     a method of a class, the name will actually include the
	     name of the class as well.  This should be harmless, but
	     is a little unfortunate.  */

	  const char *name = SYMBOL_CPLUS_DEMANGLED_NAME (symbol);
	  unsigned int prefix_len = cp_entire_prefix_len (name);

	  block_set_scope (block,
			   obsavestring (name, prefix_len, obstack),
			   obstack);
	}
    }
}