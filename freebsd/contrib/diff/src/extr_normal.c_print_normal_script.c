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
struct change {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_change ; 
 int /*<<< orphan*/  print_normal_hunk ; 
 int /*<<< orphan*/  print_script (struct change*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
print_normal_script (struct change *script)
{
  print_script (script, find_change, print_normal_hunk);
}