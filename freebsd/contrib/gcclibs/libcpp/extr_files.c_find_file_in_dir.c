#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashval_t ;
struct TYPE_15__ {int /*<<< orphan*/  nonexistent_file_hash; int /*<<< orphan*/  nonexistent_file_ob; } ;
typedef  TYPE_1__ cpp_reader ;
struct TYPE_16__ {char* name; scalar_t__ err_no; char* path; TYPE_3__* dir; } ;
typedef  TYPE_2__ _cpp_file ;
struct TYPE_17__ {char* (* construct ) (char*,TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ CPP_OPTION (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  INSERT ; 
 char* append_file_to_dir (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * htab_find_with_hash (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_string (char*) ; 
 char* obstack_copy0 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ open_file (TYPE_2__*) ; 
 int /*<<< orphan*/  open_file_failed (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pch_open_file (TYPE_1__*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  remap ; 
 char* remap_filename (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* stub1 (char*,TYPE_3__*) ; 

__attribute__((used)) static bool
find_file_in_dir (cpp_reader *pfile, _cpp_file *file, bool *invalid_pch)
{
  char *path;

  if (CPP_OPTION (pfile, remap) && (path = remap_filename (pfile, file)))
    ;
  else
    if (file->dir->construct)
      path = file->dir->construct (file->name, file->dir);
    else
      path = append_file_to_dir (file->name, file->dir);

  if (path)
    {
      hashval_t hv = htab_hash_string (path);
      char *copy;
      void **pp;

      if (htab_find_with_hash (pfile->nonexistent_file_hash, path, hv) != NULL)
	{
	  file->err_no = ENOENT;
	  return false;
	}

      file->path = path;
      if (pch_open_file (pfile, file, invalid_pch))
	return true;

      if (open_file (file))
	return true;

      if (file->err_no != ENOENT)
	{
	  open_file_failed (pfile, file, 0);
	  return true;
	}

      /* We copy the path name onto an obstack partly so that we don't
	 leak the memory, but mostly so that we don't fragment the
	 heap.  */
      copy = obstack_copy0 (&pfile->nonexistent_file_ob, path,
			    strlen (path));
      free (path);
      pp = htab_find_slot_with_hash (pfile->nonexistent_file_hash,
				     copy, hv, INSERT);
      *pp = copy;

      file->path = file->name;
    }
  else
    {
      file->err_no = ENOENT; 
      file->path = NULL;
    }

  return false;
}