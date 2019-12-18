#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_2__ {int pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 TYPE_1__* procinfo_list ; 

ptid_t
procfs_first_available (void)
{
  return pid_to_ptid (procinfo_list ? procinfo_list->pid : -1);
}