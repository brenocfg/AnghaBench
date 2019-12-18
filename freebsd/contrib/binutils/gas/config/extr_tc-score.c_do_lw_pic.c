#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ X_add_symbol; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; TYPE_2__ exp; } ;
struct TYPE_6__ {int instruction; TYPE_1__ reloc; scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ BAD_ARGS ; 
 int /*<<< orphan*/  BFD_RELOC_SCORE_GOT15 ; 
 scalar_t__ FAIL ; 
 int GP ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int end_of_line (char*) ; 
 TYPE_3__ inst ; 
 int my_get_expression (TYPE_2__*,char**) ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static void
do_lw_pic (char *str)
{
  int reg_rd;

  skip_whitespace (str);
  if (((reg_rd = reg_required_here (&str, 20, REG_TYPE_SCORE)) == (int) FAIL)
      || (skip_past_comma (&str) == (int) FAIL)
      || (my_get_expression (&inst.reloc.exp, &str) == (int) FAIL)
      || (end_of_line (str) == (int) FAIL))
    {
      return;
    }
  else
    {
      if (inst.reloc.exp.X_add_symbol == 0)
        {
          if (!inst.error)
	    inst.error = BAD_ARGS;

          return;
        }

      inst.instruction |= GP << 15;
      inst.reloc.type = BFD_RELOC_SCORE_GOT15;
    }
}