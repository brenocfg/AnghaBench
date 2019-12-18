#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  st_mode; } ;
struct TYPE_4__ {char* path; int fd; scalar_t__ err_no; TYPE_3__ st; } ;
typedef  TYPE_1__ _cpp_file ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int O_BINARY ; 
 int O_NOCTTY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fstat (int,TYPE_3__*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  set_stdin_to_binary_mode () ; 

__attribute__((used)) static bool
open_file (_cpp_file *file)
{
  if (file->path[0] == '\0')
    {
      file->fd = 0;
      set_stdin_to_binary_mode ();
    }
  else
    file->fd = open (file->path, O_RDONLY | O_NOCTTY | O_BINARY, 0666);

  if (file->fd != -1)
    {
      if (fstat (file->fd, &file->st) == 0)
	{
	  if (!S_ISDIR (file->st.st_mode))
	    {
	      file->err_no = 0;
	      return true;
	    }

	  /* Ignore a directory and continue the search.  The file we're
	     looking for may be elsewhere in the search path.  */
	  errno = ENOENT;
	}

      close (file->fd);
      file->fd = -1;
    }
  else if (errno == ENOTDIR)
    errno = ENOENT;

  file->err_no = errno;

  return false;
}