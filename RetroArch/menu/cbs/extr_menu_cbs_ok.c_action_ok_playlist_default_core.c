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
 int /*<<< orphan*/  ACTION_OK_DL_DROPDOWN_BOX_LIST_PLAYLIST_DEFAULT_CORE ; 
 int /*<<< orphan*/  generic_action_ok_displaylist_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int action_ok_playlist_default_core(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   generic_action_ok_displaylist_push(
         NULL,
         NULL, NULL, 0, idx, 0,
         ACTION_OK_DL_DROPDOWN_BOX_LIST_PLAYLIST_DEFAULT_CORE);
   return 0;
}