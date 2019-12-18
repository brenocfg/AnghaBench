#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int sy_resolved; int sy_used; } ;
typedef  TYPE_1__ symbolS ;
struct local_symbol {int /*<<< orphan*/  lsy_name; int /*<<< orphan*/  lsy_value; int /*<<< orphan*/  lsy_section; int /*<<< orphan*/ * lsy_marker; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_LOCAL_SYMFIELD_CONVERT (struct local_symbol*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_jam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_hash ; 
 int /*<<< orphan*/  local_symbol_conversion_count ; 
 scalar_t__ local_symbol_converted_p (struct local_symbol*) ; 
 int /*<<< orphan*/  local_symbol_get_frag (struct local_symbol*) ; 
 TYPE_1__* local_symbol_get_real_symbol (struct local_symbol*) ; 
 int /*<<< orphan*/  local_symbol_mark_converted (struct local_symbol*) ; 
 scalar_t__ local_symbol_resolved_p (struct local_symbol*) ; 
 int /*<<< orphan*/  local_symbol_set_real_symbol (struct local_symbol*,TYPE_1__*) ; 
 TYPE_1__* symbol_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_table_insert (TYPE_1__*) ; 

__attribute__((used)) static symbolS *
local_symbol_convert (struct local_symbol *locsym)
{
  symbolS *ret;

  assert (locsym->lsy_marker == NULL);
  if (local_symbol_converted_p (locsym))
    return local_symbol_get_real_symbol (locsym);

  ++local_symbol_conversion_count;

  ret = symbol_new (locsym->lsy_name, locsym->lsy_section, locsym->lsy_value,
		    local_symbol_get_frag (locsym));

  if (local_symbol_resolved_p (locsym))
    ret->sy_resolved = 1;

  /* Local symbols are always either defined or used.  */
  ret->sy_used = 1;

#ifdef TC_LOCAL_SYMFIELD_CONVERT
  TC_LOCAL_SYMFIELD_CONVERT (locsym, ret);
#endif

  symbol_table_insert (ret);

  local_symbol_mark_converted (locsym);
  local_symbol_set_real_symbol (locsym, ret);

  hash_jam (local_hash, locsym->lsy_name, NULL);

  return ret;
}