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
typedef  int /*<<< orphan*/  set_el_t ;
typedef  int /*<<< orphan*/ * reserv_sets_t ;
struct TYPE_2__ {int units_num; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 TYPE_1__* description ; 
 int els_in_cycle_reserv ; 
 int /*<<< orphan*/ * excl_set ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** unit_excl_set_table ; 

__attribute__((used)) static reserv_sets_t
get_excl_set (reserv_sets_t in_set)
{
  int excl_char_num;
  int chars_num;
  int i;
  int start_unit_num;
  int unit_num;

  chars_num = els_in_cycle_reserv * sizeof (set_el_t);
  memset (excl_set, 0, chars_num);
  for (excl_char_num = 0; excl_char_num < chars_num; excl_char_num++)
    if (((unsigned char *) in_set) [excl_char_num])
      for (i = CHAR_BIT - 1; i >= 0; i--)
	if ((((unsigned char *) in_set) [excl_char_num] >> i) & 1)
	  {
	    start_unit_num = excl_char_num * CHAR_BIT + i;
	    if (start_unit_num >= description->units_num)
	      return excl_set;
	    for (unit_num = 0; unit_num < els_in_cycle_reserv; unit_num++)
	      {
		excl_set [unit_num]
		  |= unit_excl_set_table [start_unit_num] [unit_num];
	      }
	  }
  return excl_set;
}