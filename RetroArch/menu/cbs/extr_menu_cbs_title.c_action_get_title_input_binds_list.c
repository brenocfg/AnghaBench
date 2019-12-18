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
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_INPUT_USER_BINDS ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,unsigned int) ; 

__attribute__((used)) static int action_get_title_input_binds_list(const char *path, const char *label,
      unsigned menu_type, char *s, size_t len)
{
   unsigned val = (((unsigned)path[0]) - 49) + 1;
   snprintf(s, len, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_INPUT_USER_BINDS), val);
   return 0;
}