#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_6__ {int dont_read; int fd; scalar_t__ err_no; scalar_t__ buffer_valid; } ;
typedef  TYPE_1__ _cpp_file ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  open_file (TYPE_1__*) ; 
 int /*<<< orphan*/  open_file_failed (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_file_guts (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static bool
read_file (cpp_reader *pfile, _cpp_file *file)
{
  /* If we already have its contents in memory, succeed immediately.  */
  if (file->buffer_valid)
    return true;

  /* If an earlier read failed for some reason don't try again.  */
  if (file->dont_read || file->err_no)
    return false;

  if (file->fd == -1 && !open_file (file))
    {
      open_file_failed (pfile, file, 0);
      return false;
    }

  file->dont_read = !read_file_guts (pfile, file);
  close (file->fd);
  file->fd = -1;

  return !file->dont_read;
}