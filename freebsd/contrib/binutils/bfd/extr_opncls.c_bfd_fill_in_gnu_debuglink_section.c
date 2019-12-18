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
struct bfd_section {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FOPEN_RB ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned long bfd_calc_gnu_debuglink_crc32 (unsigned long,unsigned char*,size_t) ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_error_no_memory ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,unsigned long,char*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ *,struct bfd_section*,char*,int /*<<< orphan*/ ,int) ; 
 char* bfd_zmalloc (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 size_t fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* lbasename (char const*) ; 
 int /*<<< orphan*/ * real_fopen (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

bfd_boolean
bfd_fill_in_gnu_debuglink_section (bfd *abfd,
				   struct bfd_section *sect,
				   const char *filename)
{
  bfd_size_type debuglink_size;
  unsigned long crc32;
  char * contents;
  bfd_size_type crc_offset;
  FILE * handle;
  static unsigned char buffer[8 * 1024];
  size_t count;

  if (abfd == NULL || sect == NULL || filename == NULL)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  /* Make sure that we can read the file.
     XXX - Should we attempt to locate the debug info file using the same
     algorithm as gdb ?  At the moment, since we are creating the
     .gnu_debuglink section, we insist upon the user providing us with a
     correct-for-section-creation-time path, but this need not conform to
     the gdb location algorithm.  */
  handle = real_fopen (filename, FOPEN_RB);
  if (handle == NULL)
    {
      bfd_set_error (bfd_error_system_call);
      return FALSE;
    }

  crc32 = 0;
  while ((count = fread (buffer, 1, sizeof buffer, handle)) > 0)
    crc32 = bfd_calc_gnu_debuglink_crc32 (crc32, buffer, count);
  fclose (handle);

  /* Strip off any path components in filename,
     now that we no longer need them.  */
  filename = lbasename (filename);

  debuglink_size = strlen (filename) + 1;
  debuglink_size += 3;
  debuglink_size &= ~3;
  debuglink_size += 4;

  contents = bfd_zmalloc (debuglink_size);
  if (contents == NULL)
    {
      /* XXX Should we delete the section from the bfd ?  */
      bfd_set_error (bfd_error_no_memory);
      return FALSE;
    }

  strcpy (contents, filename);
  crc_offset = debuglink_size - 4;

  bfd_put_32 (abfd, crc32, contents + crc_offset);

  if (! bfd_set_section_contents (abfd, sect, contents, 0, debuglink_size))
    {
      /* XXX Should we delete the section from the bfd ?  */
      free (contents);
      return FALSE;
    }

  return TRUE;
}