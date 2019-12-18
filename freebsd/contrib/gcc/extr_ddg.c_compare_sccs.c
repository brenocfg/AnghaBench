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
typedef  TYPE_1__* ddg_scc_ptr ;
struct TYPE_2__ {int recurrence_length; } ;

/* Variables and functions */

__attribute__((used)) static int
compare_sccs (const void *s1, const void *s2)
{
  int rec_l1 = (*(ddg_scc_ptr *)s1)->recurrence_length;
  int rec_l2 = (*(ddg_scc_ptr *)s2)->recurrence_length; 
  return ((rec_l2 > rec_l1) - (rec_l2 < rec_l1));
	  
}