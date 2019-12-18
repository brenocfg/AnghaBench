#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  set_el_t ;
typedef  int* reserv_sets_t ;
typedef  TYPE_1__* pattern_reserv_t ;
struct TYPE_6__ {int units_num; } ;
struct TYPE_5__ {int* reserv; struct TYPE_5__* next_pattern_reserv; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 int FALSE ; 
 int TRUE ; 
 TYPE_4__* description ; 
 int els_in_cycle_reserv ; 
 TYPE_1__** unit_absence_set_table ; 
 TYPE_1__** unit_final_absence_set_table ; 

__attribute__((used)) static int
check_absence_pattern_sets (reserv_sets_t checked_set,
			    reserv_sets_t origional_set,
			    int final_p)
{
  int char_num;
  int chars_num;
  int i;
  int start_unit_num;
  int unit_num;
  pattern_reserv_t pat_reserv;

  chars_num = els_in_cycle_reserv * sizeof (set_el_t);
  for (char_num = 0; char_num < chars_num; char_num++)
    if (((unsigned char *) origional_set) [char_num])
      for (i = CHAR_BIT - 1; i >= 0; i--)
	if ((((unsigned char *) origional_set) [char_num] >> i) & 1)
	  {
	    start_unit_num = char_num * CHAR_BIT + i;
	    if (start_unit_num >= description->units_num)
	      break;
	    for (pat_reserv = (final_p
			       ? unit_final_absence_set_table [start_unit_num]
			       : unit_absence_set_table [start_unit_num]);
		 pat_reserv != NULL;
		 pat_reserv = pat_reserv->next_pattern_reserv)
	      {
		for (unit_num = 0; unit_num < els_in_cycle_reserv; unit_num++)
		  if ((checked_set [unit_num] & pat_reserv->reserv [unit_num])
		      != pat_reserv->reserv [unit_num]
		      && pat_reserv->reserv [unit_num])
		    break;
		if (unit_num >= els_in_cycle_reserv)
		  return FALSE;
	      }
	  }
  return TRUE;
}