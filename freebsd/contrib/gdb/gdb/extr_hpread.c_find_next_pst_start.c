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
struct TYPE_2__ {int end; int start; } ;

/* Variables and functions */
 TYPE_1__* pst_syms_array ; 
 int pst_syms_count ; 

__attribute__((used)) static int
find_next_pst_start (int index)
{
  int i;

  for (i = pst_syms_count - 1; i >= 0; i--)
    if (pst_syms_array[i].end <= index)
      return (i == pst_syms_count - 1) ? 0 : pst_syms_array[i + 1].start - 1;

  if (pst_syms_array[0].start > index)
    return pst_syms_array[0].start - 1;

  return 0;
}