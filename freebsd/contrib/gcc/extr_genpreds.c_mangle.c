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
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ ,char const) ; 
 char const* obstack_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtl_obstack ; 

__attribute__((used)) static const char *
mangle (const char *name)
{
  for (; *name; name++)
    switch (*name)
      {
      case '_': obstack_grow (rtl_obstack, "__", 2); break;
      case '<':	obstack_grow (rtl_obstack, "_l", 2); break;
      case '>':	obstack_grow (rtl_obstack, "_g", 2); break;
      default: obstack_1grow (rtl_obstack, *name); break;
      }

  obstack_1grow (rtl_obstack, '\0');
  return obstack_finish (rtl_obstack);
}