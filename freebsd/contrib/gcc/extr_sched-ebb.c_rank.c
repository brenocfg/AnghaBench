#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {scalar_t__ count; scalar_t__ frequency; } ;

/* Variables and functions */
 TYPE_1__* BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rank (rtx insn1, rtx insn2)
{
  basic_block bb1 = BLOCK_FOR_INSN (insn1);
  basic_block bb2 = BLOCK_FOR_INSN (insn2);

  if (bb1->count > bb2->count
      || bb1->frequency > bb2->frequency)
    return -1;
  if (bb1->count < bb2->count
      || bb1->frequency < bb2->frequency)
    return 1;
  return 0;
}