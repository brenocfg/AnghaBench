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
typedef  int /*<<< orphan*/  unw_dyn_info_t ;
typedef  int /*<<< orphan*/  unw_addr_space_t ;

/* Variables and functions */
 int /*<<< orphan*/  unw_find_dyn_list_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

unw_word_t
libunwind_find_dyn_list (unw_addr_space_t as, unw_dyn_info_t *di, void *arg)
{
  return unw_find_dyn_list_p (as, di, arg);
}