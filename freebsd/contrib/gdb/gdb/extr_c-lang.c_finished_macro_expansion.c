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
 int /*<<< orphan*/  gdb_assert (scalar_t__) ; 
 scalar_t__ lexptr ; 
 scalar_t__ macro_expanded_text ; 
 scalar_t__ macro_original_text ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

void 
finished_macro_expansion (void)
{
  /* There'd better be something to pop back to, and we better have
     saved a pointer to the start of the expanded text.  */
  gdb_assert (macro_original_text);
  gdb_assert (macro_expanded_text);

  /* Pop back to the original text.  */
  lexptr = macro_original_text;
  macro_original_text = 0;

  /* Free the expanded text.  */
  xfree (macro_expanded_text);
  macro_expanded_text = 0;
}