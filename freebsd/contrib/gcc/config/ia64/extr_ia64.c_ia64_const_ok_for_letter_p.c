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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int CONST_OK_FOR_I (int /*<<< orphan*/ ) ; 
 int CONST_OK_FOR_J (int /*<<< orphan*/ ) ; 
 int CONST_OK_FOR_K (int /*<<< orphan*/ ) ; 
 int CONST_OK_FOR_L (int /*<<< orphan*/ ) ; 
 int CONST_OK_FOR_M (int /*<<< orphan*/ ) ; 
 int CONST_OK_FOR_N (int /*<<< orphan*/ ) ; 
 int CONST_OK_FOR_O (int /*<<< orphan*/ ) ; 
 int CONST_OK_FOR_P (int /*<<< orphan*/ ) ; 

bool
ia64_const_ok_for_letter_p (HOST_WIDE_INT value, char c)
{
  switch (c)
    {
    case 'I':
      return CONST_OK_FOR_I (value);
    case 'J':
      return CONST_OK_FOR_J (value);
    case 'K':
      return CONST_OK_FOR_K (value);
    case 'L':
      return CONST_OK_FOR_L (value);
    case 'M':
      return CONST_OK_FOR_M (value);
    case 'N':
      return CONST_OK_FOR_N (value);
    case 'O':
      return CONST_OK_FOR_O (value);
    case 'P':
      return CONST_OK_FOR_P (value);
    default:
      return false;
    }
}