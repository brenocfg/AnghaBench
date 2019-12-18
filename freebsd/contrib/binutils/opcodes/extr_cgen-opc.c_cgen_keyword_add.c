#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__* nonalpha_chars; TYPE_1__* null_entry; TYPE_1__** value_hash_table; TYPE_1__** name_hash_table; } ;
struct TYPE_8__ {scalar_t__* name; struct TYPE_8__* next_value; int /*<<< orphan*/  value; struct TYPE_8__* next_name; } ;
typedef  TYPE_1__ CGEN_KEYWORD_ENTRY ;
typedef  TYPE_2__ CGEN_KEYWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ISALNUM (scalar_t__) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  build_keyword_hash_tables (TYPE_2__*) ; 
 unsigned int hash_keyword_name (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 unsigned int hash_keyword_value (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strchr (scalar_t__*,scalar_t__) ; 
 size_t strlen (scalar_t__*) ; 

void
cgen_keyword_add (CGEN_KEYWORD *kt, CGEN_KEYWORD_ENTRY *ke)
{
  unsigned int hash;
  size_t i;

  if (kt->name_hash_table == NULL)
    build_keyword_hash_tables (kt);

  hash = hash_keyword_name (kt, ke->name, 0);
  ke->next_name = kt->name_hash_table[hash];
  kt->name_hash_table[hash] = ke;

  hash = hash_keyword_value (kt, ke->value);
  ke->next_value = kt->value_hash_table[hash];
  kt->value_hash_table[hash] = ke;

  if (ke->name[0] == 0)
    kt->null_entry = ke;

  for (i = 1; i < strlen (ke->name); i++)
    if (! ISALNUM (ke->name[i])
	&& ! strchr (kt->nonalpha_chars, ke->name[i]))
      {
	size_t idx = strlen (kt->nonalpha_chars);
	
	/* If you hit this limit, please don't just
	   increase the size of the field, instead
	   look for a better algorithm.  */
	if (idx >= sizeof (kt->nonalpha_chars) - 1)
	  abort ();
	kt->nonalpha_chars[idx] = ke->name[i];
	kt->nonalpha_chars[idx+1] = 0;
      }
}