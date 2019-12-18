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

/* Variables and functions */
#define  CONST 132 
#define  CONST_INT 131 
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  HIGH 130 
#define  LABEL_REF 129 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  flag_pic ; 
 int legitimate_constant_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic_address_needs_scratch (int /*<<< orphan*/ ) ; 

bool
constant_address_p (rtx x)
{
  switch (GET_CODE (x))
    {
    case LABEL_REF:
    case CONST_INT:
    case HIGH:
      return true;

    case CONST:
      if (flag_pic && pic_address_needs_scratch (x))
	return false;
      return legitimate_constant_p (x);

    case SYMBOL_REF:
      return !flag_pic && legitimate_constant_p (x);

    default:
      return false;
    }
}