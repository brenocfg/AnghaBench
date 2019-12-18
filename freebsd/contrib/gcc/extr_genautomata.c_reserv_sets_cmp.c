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
typedef  scalar_t__ set_el_t ;
typedef  scalar_t__* reserv_sets_t ;

/* Variables and functions */
 int els_in_reservs ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static int
reserv_sets_cmp (reserv_sets_t reservs_1, reserv_sets_t reservs_2)
{
  int reservs_num;
  set_el_t *reserv_ptr_1;
  set_el_t *reserv_ptr_2;

  gcc_assert (reservs_1 && reservs_2);
  reservs_num = els_in_reservs;
  reserv_ptr_1 = reservs_1;
  reserv_ptr_2 = reservs_2;
  while (reservs_num != 0 && *reserv_ptr_1 == *reserv_ptr_2)
    {
      reservs_num--;
      reserv_ptr_1++;
      reserv_ptr_2++;
    }
  if (reservs_num == 0)
    return 0;
  else if (*reserv_ptr_1 < *reserv_ptr_2)
    return -1;
  else
    return 1;
}