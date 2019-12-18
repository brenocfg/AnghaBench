#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* local_sym_name; int /*<<< orphan*/  real; scalar_t__ loaded; scalar_t__ next_real_file; } ;
typedef  TYPE_1__ lang_input_statement_type ;
struct TYPE_7__ {scalar_t__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  default_target ; 
 TYPE_5__ input_file_chain ; 
 int /*<<< orphan*/  lang_input_file_is_search_file_enum ; 
 int /*<<< orphan*/  load_symbols (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* new_afile (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static lang_input_statement_type *
lookup_name (const char *name)
{
  lang_input_statement_type *search;

  for (search = (lang_input_statement_type *) input_file_chain.head;
       search != NULL;
       search = (lang_input_statement_type *) search->next_real_file)
    {
      /* Use the local_sym_name as the name of the file that has
	 already been loaded as filename might have been transformed
	 via the search directory lookup mechanism.  */
      const char *filename = search->local_sym_name;

      if (filename != NULL
	  && strcmp (filename, name) == 0)
	break;
    }

  if (search == NULL)
    search = new_afile (name, lang_input_file_is_search_file_enum,
			default_target, FALSE);

  /* If we have already added this file, or this file is not real
     don't add this file.  */
  if (search->loaded || !search->real)
    return search;

  if (! load_symbols (search, NULL))
    return NULL;

  return search;
}