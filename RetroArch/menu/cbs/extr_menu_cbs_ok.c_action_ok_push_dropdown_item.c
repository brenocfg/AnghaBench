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
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 

__attribute__((used)) static int action_ok_push_dropdown_item(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
#if 0
   RARCH_LOG("dropdown: \n");
   RARCH_LOG("path: %s \n", path);
   RARCH_LOG("label: %s \n", label);
   RARCH_LOG("type: %d \n", type);
   RARCH_LOG("idx: %d \n", idx);
   RARCH_LOG("entry_idx: %d \n", entry_idx);
#endif
   return 0;
}