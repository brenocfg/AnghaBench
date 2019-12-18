#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_3__ {int used; int /*<<< orphan*/  symbol; } ;
typedef  TYPE_1__ machopic_indirection ;
struct TYPE_4__ {char* (* strip_name_encoding ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ SYMBOL_REF_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htab_find_with_hash (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_string (char const*) ; 
 int /*<<< orphan*/  machopic_indirections ; 
 int /*<<< orphan*/  mark_decl_referenced (scalar_t__) ; 
 int /*<<< orphan*/  mark_referenced (scalar_t__) ; 
 scalar_t__ maybe_get_identifier (char const*) ; 
 char* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

void
machopic_validate_stub_or_non_lazy_ptr (const char *name)
{
  machopic_indirection *p;

  p = ((machopic_indirection *)
       (htab_find_with_hash (machopic_indirections, name,
			     htab_hash_string (name))));
  if (p && ! p->used)
    {
      const char *real_name;
      tree id;

      p->used = true;

      /* Do what output_addr_const will do when we actually call it.  */
      if (SYMBOL_REF_DECL (p->symbol))
	mark_decl_referenced (SYMBOL_REF_DECL (p->symbol));

      real_name = targetm.strip_name_encoding (XSTR (p->symbol, 0));

      id = maybe_get_identifier (real_name);
      if (id)
	mark_referenced (id);
    }
}