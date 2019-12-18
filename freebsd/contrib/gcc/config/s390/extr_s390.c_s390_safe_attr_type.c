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
typedef  enum attr_type { ____Placeholder_attr_type } attr_type ;

/* Variables and functions */
 int TYPE_NONE ; 
 int get_attr_type (int /*<<< orphan*/ ) ; 
 scalar_t__ recog_memoized (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum attr_type
s390_safe_attr_type (rtx insn)
{
  if (recog_memoized (insn) >= 0)
    return get_attr_type (insn);
  else
    return TYPE_NONE;
}