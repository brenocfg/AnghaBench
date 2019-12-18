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
 scalar_t__ IS_DIR_SEPARATOR (char const) ; 
 int basename_length ; 
 char* input_basename ; 
 char* input_filename ; 
 void* input_filename_length ; 
 scalar_t__ input_stat_set ; 
 char const* input_suffix ; 
 void* strlen (char*) ; 
 int suffixed_basename_length ; 

void
set_input (const char *filename)
{
  const char *p;

  input_filename = filename;
  input_filename_length = strlen (input_filename);

  input_basename = input_filename;
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
  /* Skip drive name so 'x:foo' is handled properly.  */
  if (input_basename[1] == ':')
    input_basename += 2;
#endif
  for (p = input_basename; *p; p++)
    if (IS_DIR_SEPARATOR (*p))
      input_basename = p + 1;

  /* Find a suffix starting with the last period,
     and set basename_length to exclude that suffix.  */
  basename_length = strlen (input_basename);
  suffixed_basename_length = basename_length;
  p = input_basename + basename_length;
  while (p != input_basename && *p != '.')
    --p;
  if (*p == '.' && p != input_basename)
    {
      basename_length = p - input_basename;
      input_suffix = p + 1;
    }
  else
    input_suffix = "";

  /* If a spec for 'g', 'u', or 'U' is seen with -save-temps then
     we will need to do a stat on the input_filename.  The
     INPUT_STAT_SET signals that the stat is needed.  */
  input_stat_set = 0;
}