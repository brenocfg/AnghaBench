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
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void menu_action_setting_generic_disp_set_label(
      unsigned *w, char *s, size_t len,
      const char *path, const char *label,
      char *s2, size_t len2)
{
   *s = '\0';

   if (label)
      strlcpy(s, label, len);
   *w = (unsigned)strlen(s);

   strlcpy(s2, path, len2);
}