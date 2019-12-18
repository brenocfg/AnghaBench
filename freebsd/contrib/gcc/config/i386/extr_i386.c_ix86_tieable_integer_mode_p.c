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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  DImode 131 
#define  HImode 130 
#define  QImode 129 
#define  SImode 128 
 int TARGET_64BIT ; 
 int /*<<< orphan*/  TARGET_PARTIAL_REG_STALL ; 

__attribute__((used)) static bool
ix86_tieable_integer_mode_p (enum machine_mode mode)
{
  switch (mode)
    {
    case HImode:
    case SImode:
      return true;

    case QImode:
      return TARGET_64BIT || !TARGET_PARTIAL_REG_STALL;

    case DImode:
      return TARGET_64BIT;

    default:
      return false;
    }
}