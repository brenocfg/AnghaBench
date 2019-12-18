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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_VIRTUAL_P (scalar_t__) ; 
 int TDF_SLIM ; 
 int /*<<< orphan*/  TDI_class ; 
 int /*<<< orphan*/  TFF_PLAIN_IDENTIFIER ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 int /*<<< orphan*/  dump_array (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * dump_begin (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dump_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* type_as_string (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_vtable (tree t, tree binfo, tree vtable)
{
  int flags;
  FILE *stream = dump_begin (TDI_class, &flags);

  if (!stream)
    return;

  if (!(flags & TDF_SLIM))
    {
      int ctor_vtbl_p = TYPE_BINFO (t) != binfo;

      fprintf (stream, "%s for %s",
	       ctor_vtbl_p ? "Construction vtable" : "Vtable",
	       type_as_string (BINFO_TYPE (binfo), TFF_PLAIN_IDENTIFIER));
      if (ctor_vtbl_p)
	{
	  if (!BINFO_VIRTUAL_P (binfo))
	    fprintf (stream, " (0x%lx instance)", (unsigned long)binfo);
	  fprintf (stream, " in %s", type_as_string (t, TFF_PLAIN_IDENTIFIER));
	}
      fprintf (stream, "\n");
      dump_array (stream, vtable);
      fprintf (stream, "\n");
    }

  dump_end (TDI_class, stream);
}