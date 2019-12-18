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
struct TYPE_2__ {char* filename; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,long) ; 
 char** dirs ; 
 unsigned int dirs_in_use ; 
 TYPE_1__* files ; 
 unsigned int files_in_use ; 
 char* frag_more (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  out_byte (char) ; 
 int /*<<< orphan*/  out_uleb128 (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
out_file_list (void)
{
  size_t size;
  char *cp;
  unsigned int i;

  /* Emit directory list.  */
  for (i = 1; i < dirs_in_use; ++i)
    {
      size = strlen (dirs[i]) + 1;
      cp = frag_more (size);
      memcpy (cp, dirs[i], size);
    }
  /* Terminate it.  */
  out_byte ('\0');

  for (i = 1; i < files_in_use; ++i)
    {
      if (files[i].filename == NULL)
	{
	  as_bad (_("unassigned file number %ld"), (long) i);
	  /* Prevent a crash later, particularly for file 1.  */
	  files[i].filename = "";
	  continue;
	}

      size = strlen (files[i].filename) + 1;
      cp = frag_more (size);
      memcpy (cp, files[i].filename, size);

      out_uleb128 (files[i].dir);	/* directory number */
      out_uleb128 (0);			/* last modification timestamp */
      out_uleb128 (0);			/* filesize */
    }

  /* Terminate filename list.  */
  out_byte (0);
}