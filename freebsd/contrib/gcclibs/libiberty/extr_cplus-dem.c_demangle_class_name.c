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
struct work_stuff {int dummy; } ;
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 int consume_count (char const**) ; 
 int /*<<< orphan*/  demangle_arm_hp_template (struct work_stuff*,char const**,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
demangle_class_name (struct work_stuff *work, const char **mangled,
                     string *declp)
{
  int n;
  int success = 0;

  n = consume_count (mangled);
  if (n == -1)
    return 0;
  if ((int) strlen (*mangled) >= n)
    {
      demangle_arm_hp_template (work, mangled, n, declp);
      success = 1;
    }

  return (success);
}