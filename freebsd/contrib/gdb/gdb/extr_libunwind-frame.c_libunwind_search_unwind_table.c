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
typedef  int /*<<< orphan*/  unw_word_t ;
typedef  int /*<<< orphan*/  unw_addr_space_t ;

/* Variables and functions */
 int unw_search_unwind_table_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,int,void*) ; 

int
libunwind_search_unwind_table (void *as, long ip, void *di,
			       void *pi, int need_unwind_info, void *args)
{
  return unw_search_unwind_table_p (*(unw_addr_space_t *)as, (unw_word_t )ip, 
				    di, pi, need_unwind_info, args);
}