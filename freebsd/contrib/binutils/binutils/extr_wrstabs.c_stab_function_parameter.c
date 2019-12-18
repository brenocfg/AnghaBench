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
struct stab_write_handle {int dummy; } ;
typedef  enum debug_parm_kind { ____Placeholder_debug_parm_kind } debug_parm_kind ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
#define  DEBUG_PARM_REFERENCE 131 
#define  DEBUG_PARM_REF_REG 130 
#define  DEBUG_PARM_REG 129 
#define  DEBUG_PARM_STACK 128 
 int /*<<< orphan*/  FALSE ; 
 int N_PSYM ; 
 int N_RSYM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char,char*) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_write_symbol (struct stab_write_handle*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
stab_function_parameter (void *p, const char *name, enum debug_parm_kind kind, bfd_vma val)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  char *s, *buf;
  int stab_type;
  char kindc;

  s = stab_pop_type (info);

  switch (kind)
    {
    default:
      abort ();

    case DEBUG_PARM_STACK:
      stab_type = N_PSYM;
      kindc = 'p';
      break;

    case DEBUG_PARM_REG:
      stab_type = N_RSYM;
      kindc = 'P';
      break;

    case DEBUG_PARM_REFERENCE:
      stab_type = N_PSYM;
      kindc = 'v';
      break;

    case DEBUG_PARM_REF_REG:
      stab_type = N_RSYM;
      kindc = 'a';
      break;
    }

  buf = (char *) xmalloc (strlen (name) + strlen (s) + 3);
  sprintf (buf, "%s:%c%s", name, kindc, s);
  free (s);

  if (! stab_write_symbol (info, stab_type, 0, val, buf))
    return FALSE;

  free (buf);

  return TRUE;
}