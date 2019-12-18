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
 scalar_t__ C_FILE ; 
 scalar_t__ S_GET_STORAGE_CLASS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_dot_file_symbol (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * symbol_rootP ; 

void
coff_adjust_symtab (void)
{
  if (symbol_rootP == NULL
      || S_GET_STORAGE_CLASS (symbol_rootP) != C_FILE)
    c_dot_file_symbol ("fake", 0);
}