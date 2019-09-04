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
struct tcpcb {int /*<<< orphan*/  snd_ssthresh; TYPE_2__* t_inpcb; } ;
struct sockbuf {int sb_flags; scalar_t__ sb_hiwat; scalar_t__ sb_idealsize; } ;
struct TYPE_4__ {TYPE_1__* inp_socket; } ;
struct TYPE_3__ {struct sockbuf so_snd; } ;

/* Variables and functions */
 int SB_AUTOSIZE ; 
 int SB_TRIM ; 
 int /*<<< orphan*/  SET_SNDSB_IDEAL_SIZE (struct sockbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbreserve (struct sockbuf*,scalar_t__) ; 

void tcp_bad_rexmt_fix_sndbuf(struct tcpcb *tp)
{
	struct sockbuf *sb;
	sb = &tp->t_inpcb->inp_socket->so_snd;
	if ((sb->sb_flags & (SB_TRIM|SB_AUTOSIZE)) == (SB_TRIM|SB_AUTOSIZE)) {
		/*
		 * If there was a retransmission that was not necessary
		 * then the size of socket buffer can be restored to
		 * what it was before
		 */
		SET_SNDSB_IDEAL_SIZE(sb, tp->snd_ssthresh);
		if (sb->sb_hiwat <= sb->sb_idealsize) {
			sbreserve(sb, sb->sb_idealsize);
			sb->sb_flags &= ~SB_TRIM;
		}
	}
}