#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ at_end; scalar_t__ linenum; scalar_t__ pos; int /*<<< orphan*/  filename; struct TYPE_5__* next; } ;
typedef  TYPE_1__ file_info_type ;

/* Variables and functions */
 TYPE_1__* file_info_head ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static file_info_type *
file_info (const char *file_name)
{
  /* Find an entry with this file name.  */
  file_info_type *p = file_info_head;

  while (p != (file_info_type *) NULL)
    {
      if (strcmp (p->filename, file_name) == 0)
	return p;
      p = p->next;
    }

  /* Make new entry.  */
  p = xmalloc (sizeof (file_info_type));
  p->next = file_info_head;
  file_info_head = p;
  p->filename = xstrdup (file_name);
  p->pos = 0;
  p->linenum = 0;
  p->at_end = 0;

  return p;
}