#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct cpp_dir {int dummy; } ;
struct TYPE_15__ {TYPE_4__* buffer; } ;
typedef  TYPE_5__ cpp_reader ;
struct TYPE_11__ {scalar_t__ st_mtime; } ;
struct TYPE_16__ {int fd; TYPE_1__ st; scalar_t__ err_no; } ;
typedef  TYPE_6__ _cpp_file ;
struct TYPE_14__ {TYPE_3__* file; } ;
struct TYPE_12__ {scalar_t__ st_mtime; } ;
struct TYPE_13__ {TYPE_2__ st; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT_INCLUDE ; 
 TYPE_6__* _cpp_find_file (TYPE_5__*,char const*,struct cpp_dir*,int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 struct cpp_dir* search_path_head (TYPE_5__*,char const*,int,int /*<<< orphan*/ ) ; 

int
_cpp_compare_file_date (cpp_reader *pfile, const char *fname,
			int angle_brackets)
{
  _cpp_file *file;
  struct cpp_dir *dir;

  dir = search_path_head (pfile, fname, angle_brackets, IT_INCLUDE);
  if (!dir)
    return -1;

  file = _cpp_find_file (pfile, fname, dir, false, angle_brackets);
  if (file->err_no)
    return -1;

  if (file->fd != -1)
    {
      close (file->fd);
      file->fd = -1;
    }

  return file->st.st_mtime > pfile->buffer->file->st.st_mtime;
}