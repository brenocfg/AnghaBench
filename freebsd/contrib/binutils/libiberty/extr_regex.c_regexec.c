#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct re_registers {size_t num_regs; int /*<<< orphan*/ * start; int /*<<< orphan*/ * end; } ;
struct TYPE_6__ {int /*<<< orphan*/  rm_eo; int /*<<< orphan*/  rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
struct TYPE_7__ {int not_bol; int not_eol; int /*<<< orphan*/  regs_allocated; int /*<<< orphan*/  no_sub; } ;
typedef  TYPE_2__ regex_t ;
typedef  int boolean ;

/* Variables and functions */
 int /*<<< orphan*/  REGS_FIXED ; 
 scalar_t__ REG_NOERROR ; 
 scalar_t__ REG_NOMATCH ; 
 int REG_NOTBOL ; 
 int REG_NOTEOL ; 
 int /*<<< orphan*/ * TALLOC (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int re_search (TYPE_2__*,char const*,int,int /*<<< orphan*/ ,int,struct re_registers*) ; 
 int /*<<< orphan*/  regoff_t ; 
 int strlen (char const*) ; 

int
regexec (const regex_t *preg, const char *string, size_t nmatch,
         regmatch_t pmatch[], int eflags)
{
  int ret;
  struct re_registers regs;
  regex_t private_preg;
  int len = strlen (string);
  boolean want_reg_info = !preg->no_sub && nmatch > 0;

  private_preg = *preg;

  private_preg.not_bol = !!(eflags & REG_NOTBOL);
  private_preg.not_eol = !!(eflags & REG_NOTEOL);

  /* The user has told us exactly how many registers to return
     information about, via `nmatch'.  We have to pass that on to the
     matching routines.  */
  private_preg.regs_allocated = REGS_FIXED;

  if (want_reg_info)
    {
      regs.num_regs = nmatch;
      regs.start = TALLOC (nmatch * 2, regoff_t);
      if (regs.start == NULL)
        return (int) REG_NOMATCH;
      regs.end = regs.start + nmatch;
    }

  /* Perform the searching operation.  */
  ret = re_search (&private_preg, string, len,
                   /* start: */ 0, /* range: */ len,
                   want_reg_info ? &regs : (struct re_registers *) 0);

  /* Copy the register information to the POSIX structure.  */
  if (want_reg_info)
    {
      if (ret >= 0)
        {
          unsigned r;

          for (r = 0; r < nmatch; r++)
            {
              pmatch[r].rm_so = regs.start[r];
              pmatch[r].rm_eo = regs.end[r];
            }
        }

      /* If we needed the temporary register info, free the space now.  */
      free (regs.start);
    }

  /* We want zero return to mean success, unlike `re_search'.  */
  return ret >= 0 ? (int) REG_NOERROR : (int) REG_NOMATCH;
}