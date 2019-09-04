#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnop_ioctl_args {int a_fflag; int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_data; int /*<<< orphan*/  a_command; TYPE_2__* a_vp; } ;
struct fileproc {struct fileglob* f_fglob; } ;
struct fileglob {void* fg_data; } ;
typedef  void* caddr_t ;
struct TYPE_4__ {TYPE_1__* v_fifoinfo; } ;
struct TYPE_3__ {scalar_t__ fi_writesock; scalar_t__ fi_readsock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  bzero (struct fileproc*,int) ; 
 int soo_ioctl (struct fileproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
fifo_ioctl(struct vnop_ioctl_args *ap)
{
	struct fileproc filetmp;
	struct fileglob filefg;
	int error;

	if (ap->a_command == FIONBIO)
		return (0);
	bzero(&filetmp, sizeof(struct fileproc));
	filetmp.f_fglob = &filefg;
	if (ap->a_fflag & FREAD) {
		filetmp.f_fglob->fg_data = (caddr_t)ap->a_vp->v_fifoinfo->fi_readsock;
		error = soo_ioctl(&filetmp, ap->a_command, ap->a_data, ap->a_context);
		if (error)
			return (error);
	}
	if (ap->a_fflag & FWRITE) {
		filetmp.f_fglob->fg_data = (caddr_t)ap->a_vp->v_fifoinfo->fi_writesock;
		error = soo_ioctl(&filetmp, ap->a_command, ap->a_data, ap->a_context);
		if (error)
			return (error);
	}
	return (0);
}