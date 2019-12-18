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
struct symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 scalar_t__ STRUCT_DOMAIN ; 
 scalar_t__ SYMBOL_DOMAIN (struct symbol*) ; 
 int is_suppressed_name (int /*<<< orphan*/ ) ; 

int
ada_suppress_symbol_printing (struct symbol *sym)
{
  if (SYMBOL_DOMAIN (sym) == STRUCT_DOMAIN)
    return 1;
  else
    return is_suppressed_name (DEPRECATED_SYMBOL_NAME (sym));
}