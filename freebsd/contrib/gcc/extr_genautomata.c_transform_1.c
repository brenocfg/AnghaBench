#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct regexp {int dummy; } ;
typedef  TYPE_1__* regexp_t ;
typedef  scalar_t__ pos_t ;
struct TYPE_12__ {int repeat_num; TYPE_1__* regexp; } ;
struct TYPE_11__ {int regexps_num; int /*<<< orphan*/ * regexps; } ;
struct TYPE_10__ {scalar_t__ mode; scalar_t__ pos; } ;

/* Variables and functions */
 TYPE_8__* REGEXP_REPEAT (TYPE_1__*) ; 
 TYPE_6__* REGEXP_SEQUENCE (TYPE_1__*) ; 
 int /*<<< orphan*/  copy_insn_regexp (TYPE_1__*) ; 
 TYPE_1__* create_node (int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int regexp_transformed_p ; 
 scalar_t__ rm_repeat ; 
 scalar_t__ rm_sequence ; 

__attribute__((used)) static regexp_t
transform_1 (regexp_t regexp)
{
  int i;
  int repeat_num;
  regexp_t operand;
  pos_t pos;

  if (regexp->mode == rm_repeat)
    {
      repeat_num = REGEXP_REPEAT (regexp)->repeat_num;
      gcc_assert (repeat_num > 1);
      operand = REGEXP_REPEAT (regexp)->regexp;
      pos = regexp->mode;
      regexp = create_node (sizeof (struct regexp) + sizeof (regexp_t)
			    * (repeat_num - 1));
      regexp->mode = rm_sequence;
      regexp->pos = pos;
      REGEXP_SEQUENCE (regexp)->regexps_num = repeat_num;
      for (i = 0; i < repeat_num; i++)
	REGEXP_SEQUENCE (regexp)->regexps [i] = copy_insn_regexp (operand);
      regexp_transformed_p = 1;
    }
  return regexp;
}