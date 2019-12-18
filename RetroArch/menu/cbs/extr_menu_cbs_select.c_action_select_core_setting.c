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

/* Variables and functions */
 int action_ok_core_option_dropdown_list (char const*,char const*,unsigned int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int action_select_core_setting(const char *path, const char *label, unsigned type,
      size_t idx)
{
   return action_ok_core_option_dropdown_list(path, label, type, idx, 0);
}