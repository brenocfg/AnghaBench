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
struct TYPE_2__ {int relax_inst; int instruction; int relax_size; int bwarn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ARGS ; 
 scalar_t__ FAIL ; 
 int MAX_LITERAL_POOL_SIZE ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int /*<<< orphan*/  SET_INSN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int append_insn (char*,int /*<<< orphan*/ ) ; 
 int end_of_line (char*) ; 
 TYPE_1__ inst ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static void
do16_mv_rdrs (char *str)
{
  int reg_rd;
  int reg_rs;
  char *backupstr = NULL;

  backupstr = str;
  skip_whitespace (str);

  if ((reg_rd = reg_required_here (&str, 8, REG_TYPE_SCORE)) == (int) FAIL
      || skip_past_comma (&str) == (int) FAIL
      || (reg_rs = reg_required_here (&str, 4, REG_TYPE_SCORE)) == (int) FAIL
      || end_of_line (str) == (int) FAIL)
    {
      return;
    }
  else
    {
      /* Case 1 : mv! or mlfh!.  */
      if (reg_rd < 16)
        {
          if (reg_rs < 16)
            {
              inst.relax_inst |= (((inst.instruction >> 8) & 0xf) << 20)
                | (((inst.instruction >> 4) & 0xf) << 15) | (0xf << 10);
              inst.relax_size = 4;
            }
          else
            {
              char append_str[MAX_LITERAL_POOL_SIZE];

              sprintf (append_str, "mlfh! %s", backupstr);
              if (append_insn (append_str, TRUE) == (int) FAIL)
		return;
              /* Set bwarn as -1, so macro instruction itself will not be generated frag.  */
              inst.bwarn = -1;
            }
        }
      /* Case 2 : mhfl!.  */
      else
        {
          if (reg_rs > 16)
            {
              SET_INSN_ERROR (BAD_ARGS);
              return;
            }
          else
            {
              char append_str[MAX_LITERAL_POOL_SIZE];

              sprintf (append_str, "mhfl! %s", backupstr);
              if (append_insn (append_str, TRUE) == (int) FAIL)
		return;

              /* Set bwarn as -1, so macro instruction itself will not be generated frag.  */
              inst.bwarn = -1;
            }
        }
    }
}