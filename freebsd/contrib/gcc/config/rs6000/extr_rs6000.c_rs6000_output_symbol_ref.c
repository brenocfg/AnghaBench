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
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RS6000_OUTPUT_BASENAME (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ VTABLE_NAME_P (char const*) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,char const*) ; 

void
rs6000_output_symbol_ref (FILE *file, rtx x)
{
  /* Currently C++ toc references to vtables can be emitted before it
     is decided whether the vtable is public or private.  If this is
     the case, then the linker will eventually complain that there is
     a reference to an unknown section.  Thus, for vtables only,
     we emit the TOC reference to reference the symbol and not the
     section.  */
  const char *name = XSTR (x, 0);

  if (VTABLE_NAME_P (name))
    {
      RS6000_OUTPUT_BASENAME (file, name);
    }
  else
    assemble_name (file, name);
}