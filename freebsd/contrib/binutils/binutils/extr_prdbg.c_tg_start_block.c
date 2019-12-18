#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pr_handle {scalar_t__ parameter; char* filename; int /*<<< orphan*/  f; TYPE_1__* stack; int /*<<< orphan*/  syms; int /*<<< orphan*/  abfd; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int bfd_boolean ;
struct TYPE_2__ {char* parents; scalar_t__* method; int /*<<< orphan*/ * flavor; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  print_vma (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  translate_addresses (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
tg_start_block (void *p, bfd_vma addr)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char ab[20], kind, *partof;
  char *t;
  bfd_boolean local;

  if (info->parameter > 0)
    {
      info->parameter = 0;

      /* Delayed name.  */
      fprintf (info->f, "%s\t%s\t", info->stack->parents, info->filename);
      free (info->stack->parents);

      print_vma (addr, ab, TRUE, TRUE);
      translate_addresses (info->abfd, ab, info->f, info->syms);
      local = info->stack->flavor != NULL;
      if (info->stack->method && *info->stack->method)
	{
	  kind = 'm';
	  partof = (char *) info->stack->method;
	}
      else
	{
	  kind = 'f';
	  partof = NULL;
	  if (! info->stack->method && ! append_type (info, ")"))
	    return FALSE;
	}
      t = pop_type (info);
      if (t == NULL)
	return FALSE;
      fprintf (info->f, ";\"\tkind:%c\ttype:%s", kind, t);
      if (local)
	fputs ("\tfile:", info->f);
      if (partof)
	{
	  fprintf (info->f, "\tclass:%s", partof);
	  free (partof);
	}
      fputc ('\n', info->f);
    }

  return TRUE;
}