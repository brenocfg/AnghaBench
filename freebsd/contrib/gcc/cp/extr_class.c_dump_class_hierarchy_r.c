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
 scalar_t__ BINFO_BASE_ITERATE (scalar_t__,int,scalar_t__) ; 
 scalar_t__ BINFO_INHERITANCE_CHAIN (scalar_t__) ; 
 scalar_t__ BINFO_LOST_PRIMARY_P (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_OFFSET (scalar_t__) ; 
 scalar_t__ BINFO_PRIMARY_P (scalar_t__) ; 
 scalar_t__ BINFO_SUBVTT_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_TYPE (scalar_t__) ; 
 scalar_t__ BINFO_VIRTUAL_P (scalar_t__) ; 
 scalar_t__ BINFO_VPTR_FIELD (scalar_t__) ; 
 scalar_t__ BINFO_VPTR_INDEX (scalar_t__) ; 
 scalar_t__ BINFO_VTABLE (scalar_t__) ; 
 scalar_t__ CLASSTYPE_NEARLY_EMPTY_P (int /*<<< orphan*/ ) ; 
 char* HOST_WIDE_INT_PRINT_DEC ; 
 int TDF_SLIM ; 
 int /*<<< orphan*/  TFF_PLAIN_IDENTIFIER ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 char* expr_as_string (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ is_empty_class (int /*<<< orphan*/ ) ; 
 int maybe_indent_hierarchy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tree_low_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* type_as_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
dump_class_hierarchy_r (FILE *stream,
			int flags,
			tree binfo,
			tree igo,
			int indent)
{
  int indented = 0;
  tree base_binfo;
  int i;

  indented = maybe_indent_hierarchy (stream, indent, 0);
  fprintf (stream, "%s (0x%lx) ",
	   type_as_string (BINFO_TYPE (binfo), TFF_PLAIN_IDENTIFIER),
	   (unsigned long) binfo);
  if (binfo != igo)
    {
      fprintf (stream, "alternative-path\n");
      return igo;
    }
  igo = TREE_CHAIN (binfo);

  fprintf (stream, HOST_WIDE_INT_PRINT_DEC,
	   tree_low_cst (BINFO_OFFSET (binfo), 0));
  if (is_empty_class (BINFO_TYPE (binfo)))
    fprintf (stream, " empty");
  else if (CLASSTYPE_NEARLY_EMPTY_P (BINFO_TYPE (binfo)))
    fprintf (stream, " nearly-empty");
  if (BINFO_VIRTUAL_P (binfo))
    fprintf (stream, " virtual");
  fprintf (stream, "\n");

  indented = 0;
  if (BINFO_PRIMARY_P (binfo))
    {
      indented = maybe_indent_hierarchy (stream, indent + 3, indented);
      fprintf (stream, " primary-for %s (0x%lx)",
	       type_as_string (BINFO_TYPE (BINFO_INHERITANCE_CHAIN (binfo)),
			       TFF_PLAIN_IDENTIFIER),
	       (unsigned long)BINFO_INHERITANCE_CHAIN (binfo));
    }
  if (BINFO_LOST_PRIMARY_P (binfo))
    {
      indented = maybe_indent_hierarchy (stream, indent + 3, indented);
      fprintf (stream, " lost-primary");
    }
  if (indented)
    fprintf (stream, "\n");

  if (!(flags & TDF_SLIM))
    {
      int indented = 0;

      if (BINFO_SUBVTT_INDEX (binfo))
	{
	  indented = maybe_indent_hierarchy (stream, indent + 3, indented);
	  fprintf (stream, " subvttidx=%s",
		   expr_as_string (BINFO_SUBVTT_INDEX (binfo),
				   TFF_PLAIN_IDENTIFIER));
	}
      if (BINFO_VPTR_INDEX (binfo))
	{
	  indented = maybe_indent_hierarchy (stream, indent + 3, indented);
	  fprintf (stream, " vptridx=%s",
		   expr_as_string (BINFO_VPTR_INDEX (binfo),
				   TFF_PLAIN_IDENTIFIER));
	}
      if (BINFO_VPTR_FIELD (binfo))
	{
	  indented = maybe_indent_hierarchy (stream, indent + 3, indented);
	  fprintf (stream, " vbaseoffset=%s",
		   expr_as_string (BINFO_VPTR_FIELD (binfo),
				   TFF_PLAIN_IDENTIFIER));
	}
      if (BINFO_VTABLE (binfo))
	{
	  indented = maybe_indent_hierarchy (stream, indent + 3, indented);
	  fprintf (stream, " vptr=%s",
		   expr_as_string (BINFO_VTABLE (binfo),
				   TFF_PLAIN_IDENTIFIER));
	}

      if (indented)
	fprintf (stream, "\n");
    }

  for (i = 0; BINFO_BASE_ITERATE (binfo, i, base_binfo); i++)
    igo = dump_class_hierarchy_r (stream, flags, base_binfo, igo, indent + 2);

  return igo;
}