#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbol_flags ;
typedef  int /*<<< orphan*/ * namelist ;
struct TYPE_2__ {int /*<<< orphan*/ * names; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 size_t SYMBOL_TABLE_SIZE ; 
 size_t cur_symbol_table_size ; 
 int /*<<< orphan*/  fatal (char*) ; 
 TYPE_1__* symbol_table ; 

__attribute__((used)) static void
add_symbols (symbol_flags flags, namelist names)
{
  symbol_table[cur_symbol_table_size].flags = flags;
  symbol_table[cur_symbol_table_size].names = names;
  cur_symbol_table_size++;
  if (cur_symbol_table_size >= SYMBOL_TABLE_SIZE)
    fatal ("too many calls to add_symbols");
  symbol_table[cur_symbol_table_size].names = NULL; /* Termination.  */
}