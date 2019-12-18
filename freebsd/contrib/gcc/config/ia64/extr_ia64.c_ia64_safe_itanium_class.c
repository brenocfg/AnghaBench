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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum attr_itanium_class { ____Placeholder_attr_itanium_class } attr_itanium_class ;

/* Variables and functions */
 int ITANIUM_CLASS_UNKNOWN ; 
 int get_attr_itanium_class (int /*<<< orphan*/ ) ; 
 scalar_t__ recog_memoized (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum attr_itanium_class
ia64_safe_itanium_class (rtx insn)
{
  if (recog_memoized (insn) >= 0)
    return get_attr_itanium_class (insn);
  else
    return ITANIUM_CLASS_UNKNOWN;
}