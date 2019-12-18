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
struct print_file_list {char const* filename; char const* modname; int first; struct print_file_list* next; scalar_t__ last_line; int /*<<< orphan*/  maxline; int /*<<< orphan*/  mapsize; int /*<<< orphan*/ * map; int /*<<< orphan*/  linemap; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct print_file_list*) ; 
 int /*<<< orphan*/  index_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct print_file_list* print_files ; 
 int /*<<< orphan*/ * slurp_file (char const*,int /*<<< orphan*/ *) ; 
 struct print_file_list* xmalloc (int) ; 

__attribute__((used)) static struct print_file_list *
try_print_file_open (const char *origname, const char *modname)
{
  struct print_file_list *p;

  p = xmalloc (sizeof (struct print_file_list));

  p->map = slurp_file (modname, &p->mapsize);
  if (p->map == NULL)
    {
      free (p);
      return NULL;
    }
  
  p->linemap = index_file (p->map, p->mapsize, &p->maxline);
  p->last_line = 0;
  p->filename = origname;
  p->modname = modname;
  p->next = print_files;
  p->first = 1;
  print_files = p;
  return p;
}