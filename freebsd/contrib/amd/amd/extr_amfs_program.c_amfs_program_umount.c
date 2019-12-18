#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mf_private; } ;
typedef  TYPE_1__ mntfs ;
typedef  int /*<<< orphan*/  am_node ;

/* Variables and functions */
 int amfs_program_exec (char*) ; 

__attribute__((used)) static int
amfs_program_umount(am_node *am, mntfs *mf)
{
  return amfs_program_exec((char *) mf->mf_private);
}