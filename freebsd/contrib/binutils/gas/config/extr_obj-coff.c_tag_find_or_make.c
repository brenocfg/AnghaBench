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
typedef  int /*<<< orphan*/  symbolS ;

/* Variables and functions */
 int /*<<< orphan*/  S_GET_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_table_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tag_find (char*) ; 
 int /*<<< orphan*/  tag_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  undefined_section ; 
 int /*<<< orphan*/  zero_address_frag ; 

__attribute__((used)) static symbolS *
tag_find_or_make (char *name)
{
  symbolS *symbolP;

  if ((symbolP = tag_find (name)) == NULL)
    {
      symbolP = symbol_new (name, undefined_section,
			    0, &zero_address_frag);

      tag_insert (S_GET_NAME (symbolP), symbolP);
      symbol_table_insert (symbolP);
    }

  return symbolP;
}