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
typedef  int /*<<< orphan*/  valueT ;
struct local_symbol {char* lsy_name; int /*<<< orphan*/  lsy_value; int /*<<< orphan*/  lsy_section; int /*<<< orphan*/ * lsy_marker; } ;
typedef  int /*<<< orphan*/  segT ;
typedef  int /*<<< orphan*/  fragS ;
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */
 int /*<<< orphan*/  hash_jam (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_hash ; 
 int /*<<< orphan*/  local_symbol_count ; 
 int /*<<< orphan*/  local_symbol_set_frag (struct local_symbol*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notes ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 char* save_symbol_name (char const*) ; 

__attribute__((used)) static struct local_symbol *
local_symbol_make (const char *name, segT section, valueT value, fragS *frag)
{
  char *name_copy;
  struct local_symbol *ret;

  ++local_symbol_count;

  name_copy = save_symbol_name (name);

  ret = (struct local_symbol *) obstack_alloc (&notes, sizeof *ret);
  ret->lsy_marker = NULL;
  ret->lsy_name = name_copy;
  ret->lsy_section = section;
  local_symbol_set_frag (ret, frag);
  ret->lsy_value = value;

  hash_jam (local_hash, name_copy, (PTR) ret);

  return ret;
}