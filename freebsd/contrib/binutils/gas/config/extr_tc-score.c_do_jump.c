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
struct TYPE_5__ {scalar_t__ X_add_symbol; int X_add_number; } ;
struct TYPE_4__ {int pc_rel; int /*<<< orphan*/  type; TYPE_2__ exp; } ;
struct TYPE_6__ {TYPE_1__ reloc; void* error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_SCORE_JMP ; 
 scalar_t__ FAIL ; 
 void* _ (char*) ; 
 int end_of_line (char*) ; 
 char* input_line_pointer ; 
 TYPE_3__ inst ; 
 int my_get_expression (TYPE_2__*,char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static void
do_jump (char *str)
{
  char *save_in;

  skip_whitespace (str);
  if (my_get_expression (&inst.reloc.exp, &str) == (int) FAIL
      || end_of_line (str) == (int) FAIL)
    return;

  if (inst.reloc.exp.X_add_symbol == 0)
    {
      inst.error = _("lacking label  ");
      return;
    }

  if (((inst.reloc.exp.X_add_number & 0xff000000) != 0)
      && ((inst.reloc.exp.X_add_number & 0xff000000) != 0xff000000))
    {
      inst.error = _("invalid constant: 25 bit expression not in range -2^24..2^24");
      return;
    }

  save_in = input_line_pointer;
  input_line_pointer = str;
  inst.reloc.type = BFD_RELOC_SCORE_JMP;
  inst.reloc.pc_rel = 1;
  input_line_pointer = save_in;
}