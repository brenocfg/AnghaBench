#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ const0_rtx ; 
 scalar_t__ s390_execute_label (scalar_t__) ; 

__attribute__((used)) static bool
s390_cannot_copy_insn_p (rtx insn)
{
  rtx label = s390_execute_label (insn);
  return label && label != const0_rtx;
}