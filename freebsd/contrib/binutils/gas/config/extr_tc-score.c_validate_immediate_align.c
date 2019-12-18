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
struct TYPE_2__ {void* error; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int SUCCESS ; 
 void* _ (char*) ; 
 unsigned int _IMM10_RSHIFT_2 ; 
 unsigned int _IMM5_RSHIFT_1 ; 
 unsigned int _IMM5_RSHIFT_2 ; 
 TYPE_1__ inst ; 

__attribute__((used)) static int
validate_immediate_align (int val, unsigned int data_type)
{
  if (data_type == _IMM5_RSHIFT_1)
    {
      if (val % 2)
        {
          inst.error = _("address offset must be half word alignment");
          return (int) FAIL;
        }
    }
  else if ((data_type == _IMM5_RSHIFT_2) || (data_type == _IMM10_RSHIFT_2))
    {
      if (val % 4)
        {
          inst.error = _("address offset must be word alignment");
          return (int) FAIL;
        }
    }

  return SUCCESS;
}