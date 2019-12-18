#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  (* read_pch ) (TYPE_4__*,int /*<<< orphan*/ ,int,scalar_t__) ;} ;
struct TYPE_21__ {TYPE_5__* all_files; int /*<<< orphan*/  seen_once_only; TYPE_2__ cb; } ;
typedef  TYPE_4__ cpp_reader ;
struct TYPE_20__ {scalar_t__ st_mtime; scalar_t__ st_size; } ;
struct TYPE_22__ {int fd; scalar_t__ err_no; scalar_t__ path; int /*<<< orphan*/  buffer_valid; scalar_t__ buffer; TYPE_3__ st; int /*<<< orphan*/  name; int /*<<< orphan*/  dir; scalar_t__ once_only; struct TYPE_22__* next_file; int /*<<< orphan*/  pchname; scalar_t__ pch; TYPE_1__* cmacro; scalar_t__ stack_count; } ;
typedef  TYPE_5__ _cpp_file ;
struct TYPE_18__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NT_MACRO ; 
 int /*<<< orphan*/  _cpp_mark_file_once_only (TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ check_file_against_entries (TYPE_4__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  destroy_cpp_file (TYPE_5__*) ; 
 TYPE_5__* make_cpp_file (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ read_file (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static bool
should_stack_file (cpp_reader *pfile, _cpp_file *file, bool import)
{
  _cpp_file *f;

  /* Skip once-only files.  */
  if (file->once_only)
    return false;

  /* We must mark the file once-only if #import now, before header
     guard checks.  Otherwise, undefining the header guard might
     cause the file to be re-stacked.  */
  if (import)
    {
      _cpp_mark_file_once_only (pfile, file);

      /* Don't stack files that have been stacked before.  */
      if (file->stack_count)
	return false;
    }

  /* Skip if the file had a header guard and the macro is defined.
     PCH relies on this appearing before the PCH handler below.  */
  if (file->cmacro && file->cmacro->type == NT_MACRO)
    return false;

  /* Handle PCH files immediately; don't stack them.  */
  if (file->pch)
    {
      pfile->cb.read_pch (pfile, file->pchname, file->fd, file->path);
      close (file->fd);
      file->fd = -1;
      return false;
    }

  if (!read_file (pfile, file))
    return false;

  /* Check the file against the PCH file.  This is done before
     checking against files we've already seen, since it may save on
     I/O.  */
  if (check_file_against_entries (pfile, file, import))
    {
      /* If this isn't a #import, but yet we can't include the file,
	 that means that it was #import-ed in the PCH file,
	 so we can never include it again.  */
      if (! import)
	_cpp_mark_file_once_only (pfile, file);
      return false;
    }

  /* Now we've read the file's contents, we can stack it if there
     are no once-only files.  */
  if (!pfile->seen_once_only)
    return true;

  /* We may have read the file under a different name.  Look
     for likely candidates and compare file contents to be sure.  */
  for (f = pfile->all_files; f; f = f->next_file)
    {
      if (f == file)
	continue;

      if ((import || f->once_only)
	  && f->err_no == 0
	  && f->st.st_mtime == file->st.st_mtime
	  && f->st.st_size == file->st.st_size)
	{
	  _cpp_file *ref_file;
	  bool same_file_p = false;

	  if (f->buffer && !f->buffer_valid)
	    {
	      /* We already have a buffer but it is not valid, because
		 the file is still stacked.  Make a new one.  */
	      ref_file = make_cpp_file (pfile, f->dir, f->name);
	      ref_file->path = f->path;
	    }
	  else
	    /* The file is not stacked anymore.  We can reuse it.  */
	    ref_file = f;

	  same_file_p = read_file (pfile, ref_file)
			/* Size might have changed in read_file().  */
			&& ref_file->st.st_size == file->st.st_size
			&& !memcmp (ref_file->buffer,
				    file->buffer,
				    file->st.st_size);

	  if (f->buffer && !f->buffer_valid)
	    {
	      ref_file->path = 0;
	      destroy_cpp_file (ref_file);
	    }

	  if (same_file_p)
	    break;
	}
    }

  return f == NULL;
}