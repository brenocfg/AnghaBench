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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  TARGET_EXTIMM ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int s390_single_part (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int trunc_int_for_mode (int,int /*<<< orphan*/ ) ; 

int
s390_O_constraint_str (const char c, HOST_WIDE_INT value)
{
  if (!TARGET_EXTIMM)
    return 0;

  switch (c)
    {
    case 's':
      return trunc_int_for_mode (value, SImode) == value;

    case 'p':
      return value == 0
	|| s390_single_part (GEN_INT (value), DImode, SImode, 0) == 1;

    case 'n':
      return value == -1
	|| s390_single_part (GEN_INT (value), DImode, SImode, -1) == 1;

    default:
      gcc_unreachable ();
    }
}