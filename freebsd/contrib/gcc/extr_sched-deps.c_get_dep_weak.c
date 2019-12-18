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
typedef  int /*<<< orphan*/  dw_t ;
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
 int MAX_DEP_WEAK ; 
 int MIN_DEP_WEAK ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

dw_t
get_dep_weak (ds_t ds, ds_t type)
{
  ds = ds & type;
  switch (type)
    {
    case BEGIN_DATA: ds >>= BEGIN_DATA_BITS_OFFSET; break;
    case BE_IN_DATA: ds >>= BE_IN_DATA_BITS_OFFSET; break;
    case BEGIN_CONTROL: ds >>= BEGIN_CONTROL_BITS_OFFSET; break;
    case BE_IN_CONTROL: ds >>= BE_IN_CONTROL_BITS_OFFSET; break;
    default: gcc_unreachable ();
    }

  gcc_assert (MIN_DEP_WEAK <= ds && ds <= MAX_DEP_WEAK);
  return (dw_t) ds;
}