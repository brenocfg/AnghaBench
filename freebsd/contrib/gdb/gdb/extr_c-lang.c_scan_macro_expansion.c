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

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 char* lexptr ; 
 char* macro_expanded_text ; 
 char* macro_original_text ; 

void
scan_macro_expansion (char *expansion)
{
  /* We'd better not be trying to push the stack twice.  */
  gdb_assert (! macro_original_text);
  gdb_assert (! macro_expanded_text);

  /* Save the old lexptr value, so we can return to it when we're done
     parsing the expanded text.  */
  macro_original_text = lexptr;
  lexptr = expansion;

  /* Save the expanded text, so we can free it when we're finished.  */
  macro_expanded_text = expansion;
}