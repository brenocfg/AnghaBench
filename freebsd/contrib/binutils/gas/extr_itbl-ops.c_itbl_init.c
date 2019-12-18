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
struct itbl_entry {int /*<<< orphan*/  value; int /*<<< orphan*/  name; struct itbl_entry* next; } ;
typedef  scalar_t__ e_type ;
typedef  scalar_t__ e_processor ;

/* Variables and functions */
 int /*<<< orphan*/  append_insns_as_macros () ; 
 scalar_t__ e_nprocs ; 
 scalar_t__ e_nregtypes ; 
 scalar_t__ e_p0 ; 
 scalar_t__ e_regtype0 ; 
 struct itbl_entry** get_entries (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  itbl_have_entries ; 
 int /*<<< orphan*/  reg_section ; 
 int /*<<< orphan*/  symbol_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_table_insert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_address_frag ; 

void
itbl_init (void)
{
  struct itbl_entry *e, **es;
  e_processor procn;
  e_type type;

  if (!itbl_have_entries)
    return;

  /* Since register names don't have a prefix, put them in the symbol table so
     they can't be used as symbols.  This simplifies argument parsing as
     we can let gas parse registers for us.  */
  /* Use symbol_create instead of symbol_new so we don't try to
     output registers into the object file's symbol table.  */

  for (type = e_regtype0; type < e_nregtypes; type++)
    for (procn = e_p0; procn < e_nprocs; procn++)
      {
	es = get_entries (procn, type);
	for (e = *es; e; e = e->next)
	  {
	    symbol_table_insert (symbol_create (e->name, reg_section,
						e->value, &zero_address_frag));
	  }
      }
  append_insns_as_macros ();
}