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
typedef  scalar_t__ uint64_t ;
struct socket {int so_flags; TYPE_1__* so_cfil; } ;
struct sockbuf {int sb_flags; struct socket* sb_so; } ;
struct cfi_buf {scalar_t__ cfi_pending_last; scalar_t__ cfi_pending_first; scalar_t__ cfi_pending_mbcnt; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {struct cfi_buf cfi_rcv; struct cfi_buf cfi_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INT32_MAX ; 
 scalar_t__ IS_UDP (struct socket*) ; 
 int SB_RECV ; 
 int SOF_CONTENT_FILTER ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  cfil_sock_udp_data_pending (struct sockbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

int32_t
cfil_sock_data_pending(struct sockbuf *sb)
{
	struct socket *so = sb->sb_so;
	uint64_t pending = 0;

	if (IS_UDP(so)) {
		return (cfil_sock_udp_data_pending(sb, FALSE));
	}

	if ((so->so_flags & SOF_CONTENT_FILTER) != 0 && so->so_cfil != NULL) {
		struct cfi_buf *cfi_buf;

		socket_lock_assert_owned(so);

		if ((sb->sb_flags & SB_RECV) == 0)
			cfi_buf = &so->so_cfil->cfi_snd;
		else
			cfi_buf = &so->so_cfil->cfi_rcv;

		pending = cfi_buf->cfi_pending_last -
			cfi_buf->cfi_pending_first;

		/*
		 * If we are limited by the "chars of mbufs used" roughly
		 * adjust so we won't overcommit
		 */
		if (pending > (uint64_t)cfi_buf->cfi_pending_mbcnt)
			pending = cfi_buf->cfi_pending_mbcnt;
	}

	VERIFY(pending < INT32_MAX);

	return (int32_t)(pending);
}