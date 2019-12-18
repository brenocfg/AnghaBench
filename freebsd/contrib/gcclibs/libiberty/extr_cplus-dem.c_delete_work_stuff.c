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

/* Variables and functions */
 int /*<<< orphan*/  delete_non_B_K_work_stuff (struct work_stuff*) ; 
 int /*<<< orphan*/  squangle_mop_up (struct work_stuff*) ; 

__attribute__((used)) static void
delete_work_stuff (struct work_stuff *work)
{
  delete_non_B_K_work_stuff (work);
  squangle_mop_up (work);
}