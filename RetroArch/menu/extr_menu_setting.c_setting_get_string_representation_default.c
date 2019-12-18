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
typedef  int /*<<< orphan*/  rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_default(rarch_setting_t *setting,
      char *s, size_t len)
{
   strlcpy(s, "...", len);
}