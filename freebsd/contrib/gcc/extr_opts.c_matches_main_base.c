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
 int base_of_path (char const*,char const**) ; 
 int main_input_baselength ; 
 int /*<<< orphan*/  main_input_basename ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
matches_main_base (const char *path)
{
  /* Cache the last query. */
  static const char *last_path = NULL;
  static int last_match = 0;
  if (path != last_path)
    {
      const char *base;
      int length = base_of_path (path, &base);
      last_path = path;
      last_match = (length == main_input_baselength
                    && memcmp (base, main_input_basename, length) == 0);
    }
  return last_match;
}