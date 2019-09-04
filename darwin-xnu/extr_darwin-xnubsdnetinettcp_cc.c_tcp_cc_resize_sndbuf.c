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
struct sockbuf {int sb_flags; int /*<<< orphan*/  sb_idealsize; int /*<<< orphan*/  sb_hiwat; } ;
struct TYPE_4__ {TYPE_1__* inp_socket; } ;
struct TYPE_3__ {struct sockbuf so_snd; } ;

/* Variables and functions */
 int SB_AUTOSIZE ; 
 int SB_TRIM ; 
 int /*<<< orphan*/  SET_SNDSB_IDEAL_SIZE (struct sockbuf*,int /*<<< orphan*/ ) ; 

void tcp_cc_resize_sndbuf(struct tcpcb *tp)
{
	struct sockbuf *sb;
	/*
	 * If the send socket buffer size is bigger than ssthresh,
	 * it is time to trim it because we do not want to hold
	 * too many mbufs in the socket buffer
	 */
	sb = &tp->t_inpcb->inp_socket->so_snd;
	if (sb->sb_hiwat > tp->snd_ssthresh &&
		(sb->sb_flags & SB_AUTOSIZE)) {
		if (sb->sb_idealsize > tp->snd_ssthresh) {
			SET_SNDSB_IDEAL_SIZE(sb, tp->snd_ssthresh);
		}
		sb->sb_flags |= SB_TRIM;
	}
}