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
struct file {int f_flags; struct dvb_device* private_data; } ;
struct dvb_device {struct av7110* priv; } ;
struct av7110 {int dummy; } ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  RP_VIDEO ; 
 int /*<<< orphan*/  av7110_av_stop (struct av7110*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int dvb_generic_release (struct inode*,struct file*) ; 

__attribute__((used)) static int dvb_video_release(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct av7110 *av7110 = dvbdev->priv;

	dprintk(2, "av7110:%p, \n", av7110);

	if ((file->f_flags & O_ACCMODE) != O_RDONLY) {
		av7110_av_stop(av7110, RP_VIDEO);
	}

	return dvb_generic_release(inode, file);
}