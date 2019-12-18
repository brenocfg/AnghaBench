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
struct TYPE_3__ {scalar_t__ mixer_minor; struct TYPE_3__* next_dev; } ;
typedef  TYPE_1__ vwsnd_dev_t ;
struct inode {int dummy; } ;
struct file {TYPE_1__* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGEV (char*,struct inode*,struct file*) ; 
 int /*<<< orphan*/  DEC_USE_COUNT ; 
 int ENODEV ; 
 int /*<<< orphan*/  INC_USE_COUNT ; 
 scalar_t__ iminor (struct inode*) ; 
 TYPE_1__* vwsnd_dev_list ; 

__attribute__((used)) static int vwsnd_mixer_open(struct inode *inode, struct file *file)
{
	vwsnd_dev_t *devc;

	DBGEV("(inode=0x%p, file=0x%p)\n", inode, file);

	INC_USE_COUNT;
	for (devc = vwsnd_dev_list; devc; devc = devc->next_dev)
		if (devc->mixer_minor == iminor(inode))
			break;

	if (devc == NULL) {
		DEC_USE_COUNT;
		return -ENODEV;
	}
	file->private_data = devc;
	return 0;
}