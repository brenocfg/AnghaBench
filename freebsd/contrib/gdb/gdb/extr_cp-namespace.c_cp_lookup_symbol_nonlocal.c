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
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  domain_enum ;

/* Variables and functions */
 int /*<<< orphan*/  block_scope (struct block const*) ; 
 struct symbol* lookup_namespace_scope (char const*,char const*,struct block const*,int /*<<< orphan*/  const,struct symtab**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct symbol *
cp_lookup_symbol_nonlocal (const char *name,
			   const char *linkage_name,
			   const struct block *block,
			   const domain_enum domain,
			   struct symtab **symtab)
{
  return lookup_namespace_scope (name, linkage_name, block, domain,
				 symtab, block_scope (block), 0);
}