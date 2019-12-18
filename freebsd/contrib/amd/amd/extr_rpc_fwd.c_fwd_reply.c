#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
typedef  int u_int ;
struct TYPE_9__ {char* buf; int maxlen; int len; } ;
struct TYPE_8__ {char* buf; int /*<<< orphan*/  len; int /*<<< orphan*/  maxlen; } ;
struct TYPE_7__ {char* buf; int maxlen; int len; } ;
struct t_unitdata {TYPE_3__ udata; TYPE_2__ opt; TYPE_1__ addr; } ;
struct sockaddr_in {scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  src_addr ;
struct TYPE_10__ {int /*<<< orphan*/  rf_ptr; int /*<<< orphan*/  rf_sin; int /*<<< orphan*/  (* rf_fwd ) (int /*<<< orphan*/ ,int,struct sockaddr_in*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  rf_oldid; } ;
typedef  TYPE_4__ rpc_forward ;
typedef  int RECVFROM_FROMLEN_TYPE ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ EINTR ; 
 scalar_t__ Finishing ; 
 int MAX_PACKET_SIZE ; 
 int RPC_XID_MASK ; 
#define  RPC_XID_MOUNTD 131 
#define  RPC_XID_NFSPING 130 
#define  RPC_XID_PORTMAP 129 
#define  RPC_XID_WEBNFS 128 
 scalar_t__ TLOOK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 scalar_t__ amd_state ; 
 int /*<<< orphan*/  dlog (char*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fwd_free (TYPE_4__*) ; 
 TYPE_4__* fwd_locate (int) ; 
 int /*<<< orphan*/  fwd_sock ; 
 int htonl (int /*<<< orphan*/ ) ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 int recvfrom (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,struct sockaddr_in*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ t_errno ; 
 int t_rcvudata (int /*<<< orphan*/ ,struct t_unitdata*,int*) ; 
 int /*<<< orphan*/  t_rcvuderr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
fwd_reply(void)
{
  int len;
  u_int pkt[MAX_PACKET_SIZE / sizeof(u_int) + 1];
  u_int *pkt_int;
  u_int pkt_xid;
  int rc;
  rpc_forward *p;
  struct sockaddr_in src_addr;
  RECVFROM_FROMLEN_TYPE src_addr_len;
#ifdef HAVE_TRANSPORT_TYPE_TLI
  struct t_unitdata ud;
  int flags = 0;
#endif /* HAVE_TRANSPORT_TYPE_TLI */

  /*
   * Determine the length of the packet
   */
  len = MAX_PACKET_SIZE;

  /*
   * Read the packet and check for validity
   */
again:
  src_addr_len = sizeof(src_addr);
#ifdef HAVE_TRANSPORT_TYPE_TLI
  ud.addr.buf = (char *) &src_addr;
  ud.addr.maxlen = ud.addr.len = src_addr_len;
  ud.opt.buf = (char *) NULL;
  ud.opt.maxlen = ud.opt.len = 0;
  ud.udata.buf = (char *) pkt;
  ud.udata.maxlen = ud.udata.len = len;
  /* XXX: use flags accordingly such as if T_MORE set */
  rc = t_rcvudata(fwd_sock, &ud, &flags);
  if (rc == 0)			/* success, reset rc to length */
    rc = ud.udata.len;
  else {
    plog(XLOG_ERROR,"fwd_reply failed: t_errno=%d, errno=%d, flags=%d",t_errno,errno, flags);
    /*
     * Clear error indication, otherwise the error condition persists and
     * amd gets into an infinite loop.
     */
    if (t_errno == TLOOK)
      t_rcvuderr(fwd_sock, NULL);
  }
#else /* not HAVE_TRANSPORT_TYPE_TLI */
  rc = recvfrom(fwd_sock,
		(char *) pkt,
		len,
		0,
		(struct sockaddr *) &src_addr,
		&src_addr_len);
#endif /* not HAVE_TRANSPORT_TYPE_TLI */

  /*
   * XXX: in svr4, if the T_MORE bit of flags is set, what do
   * we then do?  -Erez
   */
  if (rc < 0 || src_addr_len != sizeof(src_addr) ||
      src_addr.sin_family != AF_INET) {
    if (rc < 0 && errno == EINTR)
      goto again;
    plog(XLOG_ERROR, "Error reading RPC reply: %m");
    goto out;
  }

  /*
   * Do no more work if finishing soon
   */
  if ((int) amd_state >= (int) Finishing)
    goto out;

  /*
   * Find packet reference
   */
  pkt_int = (u_int *) pkt;
  pkt_xid = ntohl(*pkt_int);

  switch (pkt_xid & RPC_XID_MASK) {
  case RPC_XID_PORTMAP:
    dlog("Receiving PORTMAP reply %#x", pkt_xid);
    break;
  case RPC_XID_MOUNTD:
    dlog("Receiving MOUNTD reply %#x", pkt_xid);
    break;
  case RPC_XID_NFSPING:
    dlog("Receiving NFS ping %#x", pkt_xid);
    break;
  case RPC_XID_WEBNFS:
    dlog("Receiving WebNFS lookup %#x", pkt_xid);
    break;
  default:
    dlog("UNKNOWN RPC XID %#x", pkt_xid);
    break;
  }

  p = fwd_locate(pkt_xid);
  if (!p) {
    dlog("Can't forward reply id %#x", pkt_xid);
    goto out;
  }

  if (p->rf_fwd) {
    /*
     * Put the original message id back
     * into the packet.
     */
    *pkt_int = htonl(p->rf_oldid);

    /*
     * Call forwarding function
     */
    (*p->rf_fwd) ((voidp) pkt, rc, &src_addr, &p->rf_sin, p->rf_ptr, TRUE);
  }

  /*
   * Free forwarding info
   */
  fwd_free(p);

out:;
}