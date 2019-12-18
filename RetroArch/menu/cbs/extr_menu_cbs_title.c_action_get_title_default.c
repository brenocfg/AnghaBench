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
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_SELECT_FILE ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int action_get_title_default(const char *path, const char *label,
      unsigned menu_type, char *s, size_t len)
{
   strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SELECT_FILE), len);
   strlcat(s, " ", len);
   if (!string_is_empty(path))
      strlcat(s, path, len);
   return 0;
}