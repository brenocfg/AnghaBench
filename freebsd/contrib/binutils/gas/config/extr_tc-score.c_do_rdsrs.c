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
struct TYPE_2__ {int instruction; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int /*<<< orphan*/  REG_TYPE_SCORE_SR ; 
 int /*<<< orphan*/  end_of_line (char*) ; 
 TYPE_1__ inst ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static void
do_rdsrs (char *str)
{
  skip_whitespace (str);

  /* mfsr */
  if ((inst.instruction & 0xff) == 0x50)
    {
      if (reg_required_here (&str, 20, REG_TYPE_SCORE) != (int) FAIL
          && skip_past_comma (&str) != (int) FAIL
          && reg_required_here (&str, 10, REG_TYPE_SCORE_SR) != (int) FAIL)
	end_of_line (str);
    }
  else
    {
      if (reg_required_here (&str, 15, REG_TYPE_SCORE) != (int) FAIL
          && skip_past_comma (&str) != (int) FAIL)
	reg_required_here (&str, 10, REG_TYPE_SCORE_SR);
    }
}