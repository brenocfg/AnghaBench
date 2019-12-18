#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct TYPE_6__ {TYPE_1__ mach; } ;
struct TYPE_5__ {int busy; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_3__ dmasound ; 
 TYPE_2__ mixer ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mixer_open(struct inode *inode, struct file *file)
{
	if (!try_module_get(dmasound.mach.owner))
		return -ENODEV;
	mixer.busy = 1;
	return 0;
}