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
struct autofs_info {int /*<<< orphan*/  (* free ) (struct autofs_info*) ;TYPE_1__* dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/ * d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct autofs_info*) ; 
 int /*<<< orphan*/  stub1 (struct autofs_info*) ; 

void autofs4_free_ino(struct autofs_info *ino)
{
	if (ino->dentry) {
		ino->dentry->d_fsdata = NULL;
		ino->dentry = NULL;
	}
	if (ino->free)
		(ino->free)(ino);
	kfree(ino);
}