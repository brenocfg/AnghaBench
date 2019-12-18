#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct name_list* exclude_name_list; } ;
struct wildcard_list {TYPE_1__ spec; } ;
struct name_list {int /*<<< orphan*/  name; struct name_list* next; } ;
typedef  int /*<<< orphan*/  lang_wild_statement_type ;
struct TYPE_12__ {TYPE_3__* the_bfd; int /*<<< orphan*/ * filename; } ;
typedef  TYPE_4__ lang_input_statement_type ;
typedef  int /*<<< orphan*/  (* callback_t ) (int /*<<< orphan*/ *,struct wildcard_list*,int /*<<< orphan*/ *,TYPE_4__*,void*) ;
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_11__ {TYPE_2__* my_archive; } ;
struct TYPE_10__ {int /*<<< orphan*/ * filename; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ fnmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct wildcard_list*,int /*<<< orphan*/ *,TYPE_4__*,void*) ; 
 int wildcardp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
walk_wild_consider_section (lang_wild_statement_type *ptr,
			    lang_input_statement_type *file,
			    asection *s,
			    struct wildcard_list *sec,
			    callback_t callback,
			    void *data)
{
  bfd_boolean skip = FALSE;
  struct name_list *list_tmp;

  /* Don't process sections from files which were
     excluded.  */
  for (list_tmp = sec->spec.exclude_name_list;
       list_tmp;
       list_tmp = list_tmp->next)
    {
      bfd_boolean is_wildcard = wildcardp (list_tmp->name);
      if (is_wildcard)
	skip = fnmatch (list_tmp->name, file->filename, 0) == 0;
      else
	skip = strcmp (list_tmp->name, file->filename) == 0;

      /* If this file is part of an archive, and the archive is
	 excluded, exclude this file.  */
      if (! skip && file->the_bfd != NULL
	  && file->the_bfd->my_archive != NULL
	  && file->the_bfd->my_archive->filename != NULL)
	{
	  if (is_wildcard)
	    skip = fnmatch (list_tmp->name,
			    file->the_bfd->my_archive->filename,
			    0) == 0;
	  else
	    skip = strcmp (list_tmp->name,
			   file->the_bfd->my_archive->filename) == 0;
	}

      if (skip)
	break;
    }

  if (!skip)
    (*callback) (ptr, sec, s, file, data);
}