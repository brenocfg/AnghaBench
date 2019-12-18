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
struct TYPE_2__ {int /*<<< orphan*/ * idal_buf; } ;
struct tape_device {int required_tapemarks; TYPE_1__ char_data; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int) ; 
 int /*<<< orphan*/  MTREW ; 
 int /*<<< orphan*/  MTWEOF ; 
 int /*<<< orphan*/  idal_buffer_free (int /*<<< orphan*/ *) ; 
 int iminor (struct inode*) ; 
 scalar_t__ tape_mtop (struct tape_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tape_put_device (struct tape_device*) ; 
 int /*<<< orphan*/  tape_release (struct tape_device*) ; 
 int /*<<< orphan*/  tape_std_terminate_write (struct tape_device*) ; 

__attribute__((used)) static int
tapechar_release(struct inode *inode, struct file *filp)
{
	struct tape_device *device;

	DBF_EVENT(6, "TCHAR:release: %x\n", iminor(inode));
	device = (struct tape_device *) filp->private_data;

	/*
	 * If this is the rewinding tape minor then rewind. In that case we
	 * write all required tapemarks. Otherwise only one to terminate the
	 * file.
	 */
	if ((iminor(inode) & 1) != 0) {
		if (device->required_tapemarks)
			tape_std_terminate_write(device);
		tape_mtop(device, MTREW, 1);
	} else {
		if (device->required_tapemarks > 1) {
			if (tape_mtop(device, MTWEOF, 1) == 0)
				device->required_tapemarks--;
		}
	}

	if (device->char_data.idal_buf != NULL) {
		idal_buffer_free(device->char_data.idal_buf);
		device->char_data.idal_buf = NULL;
	}
	tape_release(device);
	filp->private_data = tape_put_device(device);

	return 0;
}