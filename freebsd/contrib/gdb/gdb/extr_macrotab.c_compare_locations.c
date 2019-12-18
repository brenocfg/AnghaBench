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
struct macro_source_file {int included_at_line; struct macro_source_file* included_by; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 int inclusion_depth (struct macro_source_file*) ; 

__attribute__((used)) static int
compare_locations (struct macro_source_file *file1, int line1, 
                   struct macro_source_file *file2, int line2)
{
  /* We want to treat positions in an #included file as coming *after*
     the line containing the #include, but *before* the line after the
     include.  As we walk up the #inclusion tree toward the main
     source file, we update fileX and lineX as we go; includedX
     indicates whether the original position was from the #included
     file.  */
  int included1 = 0;
  int included2 = 0;

  /* If a file is zero, that means "end of compilation unit."  Handle
     that specially.  */
  if (! file1)
    {
      if (! file2)
        return 0;
      else
        return 1;
    }
  else if (! file2)
    return -1;

  /* If the two files are not the same, find their common ancestor in
     the #inclusion tree.  */
  if (file1 != file2)
    {
      /* If one file is deeper than the other, walk up the #inclusion
         chain until the two files are at least at the same *depth*.
         Then, walk up both files in synchrony until they're the same
         file.  That file is the common ancestor.  */
      int depth1 = inclusion_depth (file1);
      int depth2 = inclusion_depth (file2);

      /* Only one of these while loops will ever execute in any given
         case.  */
      while (depth1 > depth2)
        {
          line1 = file1->included_at_line;
          file1 = file1->included_by;
          included1 = 1;
          depth1--;
        }
      while (depth2 > depth1)
        {
          line2 = file2->included_at_line;
          file2 = file2->included_by;
          included2 = 1;
          depth2--;
        }

      /* Now both file1 and file2 are at the same depth.  Walk toward
         the root of the tree until we find where the branches meet.  */
      while (file1 != file2)
        {
          line1 = file1->included_at_line;
          file1 = file1->included_by;
          /* At this point, we know that the case the includedX flags
             are trying to deal with won't come up, but we'll just
             maintain them anyway.  */
          included1 = 1;

          line2 = file2->included_at_line;
          file2 = file2->included_by;
          included2 = 1;

          /* Sanity check.  If file1 and file2 are really from the
             same compilation unit, then they should both be part of
             the same tree, and this shouldn't happen.  */
          gdb_assert (file1 && file2);
        }
    }

  /* Now we've got two line numbers in the same file.  */
  if (line1 == line2)
    {
      /* They can't both be from #included files.  Then we shouldn't
         have walked up this far.  */
      gdb_assert (! included1 || ! included2);

      /* Any #included position comes after a non-#included position
         with the same line number in the #including file.  */
      if (included1)
        return 1;
      else if (included2)
        return -1;
      else
        return 0;
    }
  else
    return line1 - line2;
}