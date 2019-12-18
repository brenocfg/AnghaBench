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
struct type {int dummy; } ;

/* Variables and functions */
 int annotation_level ; 
 int /*<<< orphan*/  print_value_flags (struct type*) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 

void
annotate_array_section_begin (int index, struct type *elttype)
{
  if (annotation_level == 2)
    {
      printf_filtered ("\n\032\032array-section-begin %d ", index);
      print_value_flags (elttype);
      printf_filtered ("\n");
    }
}