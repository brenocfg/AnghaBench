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
typedef  int /*<<< orphan*/  core_option_lbl ;
typedef  int /*<<< orphan*/  core_option_idx ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_OK_DL_DROPDOWN_BOX_LIST ; 
 int /*<<< orphan*/  generic_action_ok_displaylist_push (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

int action_ok_core_option_dropdown_list(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   char core_option_lbl[256];
   char core_option_idx[256];
   snprintf(core_option_lbl, sizeof(core_option_lbl), "core_option_%d", (int)idx);
   snprintf(core_option_idx, sizeof(core_option_idx), "%d",
         type);

   generic_action_ok_displaylist_push(
         core_option_lbl, NULL,
         core_option_idx, 0, idx, 0,
         ACTION_OK_DL_DROPDOWN_BOX_LIST);
   return 0;
}