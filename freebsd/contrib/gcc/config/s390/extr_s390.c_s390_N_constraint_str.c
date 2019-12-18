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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int DImode ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int HImode ; 
 int QImode ; 
 int SImode ; 
 int s390_single_part (int /*<<< orphan*/ ,int,int,int) ; 

int
s390_N_constraint_str (const char *str, HOST_WIDE_INT value)
{
  enum machine_mode mode, part_mode;
  int def;
  int part, part_goal;


  if (str[0] == 'x')
    part_goal = -1;
  else
    part_goal = str[0] - '0';

  switch (str[1])
    {
    case 'Q':
      part_mode = QImode;
      break;
    case 'H':
      part_mode = HImode;
      break;
    case 'S':
      part_mode = SImode;
      break;
    default:
      return 0;
    }

  switch (str[2])
    {
    case 'H':
      mode = HImode;
      break;
    case 'S':
      mode = SImode;
      break;
    case 'D':
      mode = DImode;
      break;
    default:
      return 0;
    }

  switch (str[3])
    {
    case '0':
      def = 0;
      break;
    case 'F':
      def = -1;
      break;
    default:
      return 0;
    }

  if (GET_MODE_SIZE (mode) <= GET_MODE_SIZE (part_mode))
    return 0;

  part = s390_single_part (GEN_INT (value), mode, part_mode, def);
  if (part < 0)
    return 0;
  if (part_goal != -1 && part_goal != part)
    return 0;

  return 1;
}