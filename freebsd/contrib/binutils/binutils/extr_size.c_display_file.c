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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_archive ; 
 scalar_t__ bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_nonfatal (char*) ; 
 int /*<<< orphan*/ * bfd_openr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_archive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_bfd (int /*<<< orphan*/ *) ; 
 int get_file_size (char*) ; 
 int return_code ; 
 int /*<<< orphan*/  target ; 

__attribute__((used)) static void
display_file (char *filename)
{
  bfd *file;

  if (get_file_size (filename) < 1)
    {
      return_code = 1;
      return;
    }

  file = bfd_openr (filename, target);
  if (file == NULL)
    {
      bfd_nonfatal (filename);
      return_code = 1;
      return;
    }

  if (bfd_check_format (file, bfd_archive))
    display_archive (file);
  else
    display_bfd (file);

  if (!bfd_close (file))
    {
      bfd_nonfatal (filename);
      return_code = 1;
      return;
    }
}