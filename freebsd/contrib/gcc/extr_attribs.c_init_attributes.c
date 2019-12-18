#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* name; int min_length; int max_length; scalar_t__ type_required; int /*<<< orphan*/  function_type_required; int /*<<< orphan*/  decl_required; } ;
struct TYPE_7__ {TYPE_3__* format_attribute_table; TYPE_3__* attribute_table; TYPE_3__* common_attribute_table; } ;
struct TYPE_6__ {TYPE_3__* attribute_table; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__**) ; 
 TYPE_3__** attribute_tables ; 
 int attributes_initialized ; 
 TYPE_3__* empty_attribute_table ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_2__ lang_hooks ; 
 int strcmp (char*,char*) ; 
 int strlen (char const*) ; 
 TYPE_1__ targetm ; 

__attribute__((used)) static void
init_attributes (void)
{
  size_t i;

  attribute_tables[0] = lang_hooks.common_attribute_table;
  attribute_tables[1] = lang_hooks.attribute_table;
  attribute_tables[2] = lang_hooks.format_attribute_table;
  attribute_tables[3] = targetm.attribute_table;

  /* Translate NULL pointers to pointers to the empty table.  */
  for (i = 0; i < ARRAY_SIZE (attribute_tables); i++)
    if (attribute_tables[i] == NULL)
      attribute_tables[i] = empty_attribute_table;

#ifdef ENABLE_CHECKING
  /* Make some sanity checks on the attribute tables.  */
  for (i = 0; i < ARRAY_SIZE (attribute_tables); i++)
    {
      int j;

      for (j = 0; attribute_tables[i][j].name != NULL; j++)
	{
	  /* The name must not begin and end with __.  */
	  const char *name = attribute_tables[i][j].name;
	  int len = strlen (name);

	  gcc_assert (!(name[0] == '_' && name[1] == '_'
			&& name[len - 1] == '_' && name[len - 2] == '_'));

	  /* The minimum and maximum lengths must be consistent.  */
	  gcc_assert (attribute_tables[i][j].min_length >= 0);

	  gcc_assert (attribute_tables[i][j].max_length == -1
		      || (attribute_tables[i][j].max_length
			  >= attribute_tables[i][j].min_length));

	  /* An attribute cannot require both a DECL and a TYPE.  */
	  gcc_assert (!attribute_tables[i][j].decl_required
		      || !attribute_tables[i][j].type_required);

	  /* If an attribute requires a function type, in particular
	     it requires a type.  */
	  gcc_assert (!attribute_tables[i][j].function_type_required
		      || attribute_tables[i][j].type_required);
	}
    }

  /* Check that each name occurs just once in each table.  */
  for (i = 0; i < ARRAY_SIZE (attribute_tables); i++)
    {
      int j, k;
      for (j = 0; attribute_tables[i][j].name != NULL; j++)
	for (k = j + 1; attribute_tables[i][k].name != NULL; k++)
	  gcc_assert (strcmp (attribute_tables[i][j].name,
			      attribute_tables[i][k].name));
    }
  /* Check that no name occurs in more than one table.  */
  for (i = 0; i < ARRAY_SIZE (attribute_tables); i++)
    {
      size_t j, k, l;

      for (j = i + 1; j < ARRAY_SIZE (attribute_tables); j++)
	for (k = 0; attribute_tables[i][k].name != NULL; k++)
	  for (l = 0; attribute_tables[j][l].name != NULL; l++)
	    gcc_assert (strcmp (attribute_tables[i][k].name,
				attribute_tables[j][l].name));
    }
#endif

  attributes_initialized = true;
}