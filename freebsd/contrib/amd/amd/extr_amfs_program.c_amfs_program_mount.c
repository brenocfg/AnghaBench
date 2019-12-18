#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* mf_fo; } ;
typedef  TYPE_2__ mntfs ;
typedef  int /*<<< orphan*/  am_node ;
struct TYPE_4__ {int /*<<< orphan*/  opt_mount; } ;

/* Variables and functions */
 int amfs_program_exec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amfs_program_mount(am_node *am, mntfs *mf)
{
  return amfs_program_exec(mf->mf_fo->opt_mount);
}