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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct TYPE_6__ {int /*<<< orphan*/  sb_sel; int /*<<< orphan*/  sb_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  sb_sel; int /*<<< orphan*/  sb_flags; } ;
struct socket {int so_state; TYPE_3__ so_rcv; int /*<<< orphan*/  so_oobmark; TYPE_2__ so_snd; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_4__ {scalar_t__ fg_data; } ;

/* Variables and functions */
#define  FREAD 129 
#define  FWRITE 128 
 int /*<<< orphan*/  SB_SEL ; 
 int SS_RCVATMARK ; 
 scalar_t__ mac_socket_check_select (int /*<<< orphan*/ ,struct socket*,int) ; 
 int /*<<< orphan*/  selrecord (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int /*<<< orphan*/  soreadable (struct socket*) ; 
 int /*<<< orphan*/  sowriteable (struct socket*) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
soo_select(struct fileproc *fp, int which, void *wql, vfs_context_t ctx)
{
	struct socket *so = (struct socket *)fp->f_fglob->fg_data;
	int retnum = 0;
	proc_t procp;

	if (so == NULL || so == (struct socket *)-1)
		return (0);

	procp = vfs_context_proc(ctx);

#if CONFIG_MACF_SOCKET
	if (mac_socket_check_select(vfs_context_ucred(ctx), so, which) != 0)
		return (0);
#endif /* CONFIG_MACF_SOCKET */


	socket_lock(so, 1);
	switch (which) {

	case FREAD:
		so->so_rcv.sb_flags |= SB_SEL;
		if (soreadable(so)) {
			retnum = 1;
			so->so_rcv.sb_flags &= ~SB_SEL;
			goto done;
		}
		selrecord(procp, &so->so_rcv.sb_sel, wql);
		break;

	case FWRITE:
		so->so_snd.sb_flags |= SB_SEL;
		if (sowriteable(so)) {
			retnum = 1;
			so->so_snd.sb_flags &= ~SB_SEL;
			goto done;
		}
		selrecord(procp, &so->so_snd.sb_sel, wql);
		break;

	case 0:
		so->so_rcv.sb_flags |= SB_SEL;
		if (so->so_oobmark || (so->so_state & SS_RCVATMARK)) {
			retnum = 1;
			so->so_rcv.sb_flags &= ~SB_SEL;
			goto done;
		}
		selrecord(procp, &so->so_rcv.sb_sel, wql);
		break;
	}

done:
	socket_unlock(so, 1);
	return (retnum);
}