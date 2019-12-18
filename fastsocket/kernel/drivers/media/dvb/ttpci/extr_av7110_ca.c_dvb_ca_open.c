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
struct inode {int dummy; } ;
struct file {struct dvb_device* private_data; } ;
struct dvb_device {struct av7110* priv; } ;
struct av7110 {int /*<<< orphan*/  ci_wbuffer; int /*<<< orphan*/  ci_rbuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_ll_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int dvb_generic_open (struct inode*,struct file*) ; 

__attribute__((used)) static int dvb_ca_open(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct av7110 *av7110 = dvbdev->priv;
	int err = dvb_generic_open(inode, file);

	dprintk(8, "av7110:%p\n",av7110);

	if (err < 0)
		return err;
	ci_ll_flush(&av7110->ci_rbuffer, &av7110->ci_wbuffer);
	return 0;
}