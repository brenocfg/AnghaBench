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
typedef  char reg_pref ;
struct reg_info_data {struct reg_info_data* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  heap ; 
 struct reg_info_data* reg_info_head ; 
 int /*<<< orphan*/  reg_info_p ; 
 scalar_t__ reg_n_info ; 
 scalar_t__ reg_n_max ; 
 char* reg_pref_buffer ; 
 scalar_t__ regno_allocated ; 
 short* renumber ; 

void
free_reg_info (void)
{
  if (reg_n_info)
    {
      struct reg_info_data *reg_data;
      struct reg_info_data *reg_next;

      VEC_free (reg_info_p, heap, reg_n_info);
      for (reg_data = reg_info_head; reg_data; reg_data = reg_next)
	{
	  reg_next = reg_data->next;
	  free ((char *) reg_data);
	}

      free (reg_pref_buffer);
      reg_pref_buffer = (struct reg_pref *) 0;
      reg_info_head = (struct reg_info_data *) 0;
      renumber = (short *) 0;
    }
  regno_allocated = 0;
  reg_n_max = 0;
}