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
struct ieee_var {char const* name; unsigned long namlen; } ;
struct TYPE_2__ {int alloc; struct ieee_var* vars; } ;
struct ieee_info {TYPE_1__ vars; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ieee_error (struct ieee_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_read_id (struct ieee_info*,int /*<<< orphan*/  const**,char const**,unsigned long*) ; 
 int /*<<< orphan*/  ieee_read_number (struct ieee_info*,int /*<<< orphan*/  const**,int*) ; 
 int /*<<< orphan*/  memset (struct ieee_var*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ xrealloc (struct ieee_var*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
parse_ieee_nn (struct ieee_info *info, const bfd_byte **pp)
{
  const bfd_byte *nn_start;
  bfd_vma varindx;
  const char *name;
  unsigned long namlen;

  nn_start = *pp;

  if (! ieee_read_number (info, pp, &varindx)
      || ! ieee_read_id (info, pp, &name, &namlen))
    return FALSE;

  if (varindx < 32)
    {
      ieee_error (info, nn_start, _("illegal variable index"));
      return FALSE;
    }
  varindx -= 32;

  if (varindx >= info->vars.alloc)
    {
      unsigned int alloc;

      alloc = info->vars.alloc;
      if (alloc == 0)
	alloc = 4;
      while (varindx >= alloc)
	alloc *= 2;
      info->vars.vars = ((struct ieee_var *)
			 xrealloc (info->vars.vars,
				   alloc * sizeof *info->vars.vars));
      memset (info->vars.vars + info->vars.alloc, 0,
	      (alloc - info->vars.alloc) * sizeof *info->vars.vars);
      info->vars.alloc = alloc;
    }

  info->vars.vars[varindx].name = name;
  info->vars.vars[varindx].namlen = namlen;

  return TRUE;
}