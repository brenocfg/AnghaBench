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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  d_session; int /*<<< orphan*/  d_tunnel; } ;
struct pppol2tp_session {int /*<<< orphan*/  ns; int /*<<< orphan*/  name; int /*<<< orphan*/  debug; scalar_t__ send_seq; TYPE_1__ tunnel_addr; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  L2TP_HDRFLAG_S ; 
 int /*<<< orphan*/  L2TP_HDR_VER ; 
 int /*<<< orphan*/  PPPOL2TP_MSG_SEQ ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pppol2tp_build_l2tp_header(struct pppol2tp_session *session,
				       void *buf)
{
	__be16 *bufp = buf;
	u16 flags = L2TP_HDR_VER;

	if (session->send_seq)
		flags |= L2TP_HDRFLAG_S;

	/* Setup L2TP header.
	 * FIXME: Can this ever be unaligned? Is direct dereferencing of
	 * 16-bit header fields safe here for all architectures?
	 */
	*bufp++ = htons(flags);
	*bufp++ = htons(session->tunnel_addr.d_tunnel);
	*bufp++ = htons(session->tunnel_addr.d_session);
	if (session->send_seq) {
		*bufp++ = htons(session->ns);
		*bufp++ = 0;
		session->ns++;
		PRINTK(session->debug, PPPOL2TP_MSG_SEQ, KERN_DEBUG,
		       "%s: updated ns to %hu\n", session->name, session->ns);
	}
}