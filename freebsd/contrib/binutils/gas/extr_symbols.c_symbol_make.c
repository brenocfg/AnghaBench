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
typedef  int /*<<< orphan*/  symbolS ;

/* Variables and functions */
 int /*<<< orphan*/ * md_undefined_symbol (char*) ; 
 int /*<<< orphan*/ * symbol_new (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  undefined_section ; 
 int /*<<< orphan*/  zero_address_frag ; 

symbolS *
symbol_make (const char *name)
{
  symbolS *symbolP;

  /* Let the machine description default it, e.g. for register names.  */
  symbolP = md_undefined_symbol ((char *) name);

  if (!symbolP)
    symbolP = symbol_new (name, undefined_section, (valueT) 0, &zero_address_frag);

  return (symbolP);
}