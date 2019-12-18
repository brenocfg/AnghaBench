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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {char const* single; char const** multi; char const* (* function ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int output_format; TYPE_1__ output; } ;
struct TYPE_5__ {int /*<<< orphan*/  operand; } ;

/* Variables and functions */
#define  INSN_OUTPUT_FORMAT_FUNCTION 130 
#define  INSN_OUTPUT_FORMAT_MULTI 129 
#define  INSN_OUTPUT_FORMAT_SINGLE 128 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 TYPE_3__* insn_data ; 
 TYPE_2__ recog_data ; 
 char const* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t which_alternative ; 

const char *
get_insn_template (int code, rtx insn)
{
  switch (insn_data[code].output_format)
    {
    case INSN_OUTPUT_FORMAT_SINGLE:
      return insn_data[code].output.single;
    case INSN_OUTPUT_FORMAT_MULTI:
      return insn_data[code].output.multi[which_alternative];
    case INSN_OUTPUT_FORMAT_FUNCTION:
      gcc_assert (insn);
      return (*insn_data[code].output.function) (recog_data.operand, insn);

    default:
      gcc_unreachable ();
    }
}