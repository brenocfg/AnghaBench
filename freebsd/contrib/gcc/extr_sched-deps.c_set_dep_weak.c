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
typedef  scalar_t__ dw_t ;
typedef  int ds_t ;

/* Variables and functions */
#define  BEGIN_CONTROL 131 
 int BEGIN_CONTROL_BITS_OFFSET ; 
#define  BEGIN_DATA 130 
 int BEGIN_DATA_BITS_OFFSET ; 
#define  BE_IN_CONTROL 129 
 int BE_IN_CONTROL_BITS_OFFSET ; 
#define  BE_IN_DATA 128 
 int BE_IN_DATA_BITS_OFFSET ; 
 scalar_t__ MAX_DEP_WEAK ; 
 scalar_t__ MIN_DEP_WEAK ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

ds_t
set_dep_weak (ds_t ds, ds_t type, dw_t dw)
{
  gcc_assert (MIN_DEP_WEAK <= dw && dw <= MAX_DEP_WEAK);

  ds &= ~type;
  switch (type)
    {
    case BEGIN_DATA: ds |= ((ds_t) dw) << BEGIN_DATA_BITS_OFFSET; break;
    case BE_IN_DATA: ds |= ((ds_t) dw) << BE_IN_DATA_BITS_OFFSET; break;
    case BEGIN_CONTROL: ds |= ((ds_t) dw) << BEGIN_CONTROL_BITS_OFFSET; break;
    case BE_IN_CONTROL: ds |= ((ds_t) dw) << BE_IN_CONTROL_BITS_OFFSET; break;
    default: gcc_unreachable ();
    }
  return ds;
}