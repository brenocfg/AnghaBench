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
struct stab_write_handle {scalar_t__ nesting; int fun_offset; int symbols_size; } ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  N_FUN ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,float,char*) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_write_symbol (struct stab_write_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
stab_start_function (void *p, const char *name, bfd_boolean globalp)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  char *rettype, *buf;

  assert (info->nesting == 0 && info->fun_offset == -1);

  rettype = stab_pop_type (info);

  buf = (char *) xmalloc (strlen (name) + strlen (rettype) + 3);
  sprintf (buf, "%s:%c%s", name,
	   globalp ? 'F' : 'f',
	   rettype);

  /* We don't know the value now, so we set it in start_block.  */
  info->fun_offset = info->symbols_size;

  if (! stab_write_symbol (info, N_FUN, 0, 0, buf))
    return FALSE;

  free (buf);

  return TRUE;
}