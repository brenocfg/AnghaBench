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
typedef  scalar_t__ rtx ;
struct TYPE_2__ {scalar_t__ insn; } ;

/* Variables and functions */
 scalar_t__ INSN_CODE (scalar_t__) ; 
 int /*<<< orphan*/  extract_insn (scalar_t__) ; 
 TYPE_1__ recog_data ; 

void
extract_insn_cached (rtx insn)
{
  if (recog_data.insn == insn && INSN_CODE (insn) >= 0)
    return;
  extract_insn (insn);
  recog_data.insn = insn;
}