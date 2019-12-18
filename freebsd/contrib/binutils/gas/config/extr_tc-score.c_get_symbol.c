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
 int get_symbol_end () ; 
 char* input_line_pointer ; 
 scalar_t__ symbol_find_or_make (char*) ; 

__attribute__((used)) static symbolS *
get_symbol (void)
{
  int c;
  char *name;
  symbolS *p;

  name = input_line_pointer;
  c = get_symbol_end ();
  p = (symbolS *) symbol_find_or_make (name);
  *input_line_pointer = c;
  return p;
}