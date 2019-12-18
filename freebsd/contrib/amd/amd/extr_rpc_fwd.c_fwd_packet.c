#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_12__ {char* buf; int maxlen; int len; } ;
struct TYPE_11__ {char* buf; scalar_t__ len; scalar_t__ maxlen; } ;
struct TYPE_10__ {char* buf; int maxlen; int len; } ;
struct t_unitdata {TYPE_4__ udata; TYPE_3__ opt; TYPE_2__ addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_13__ {int rf_xid; int /*<<< orphan*/  rf_ptr; struct sockaddr_in rf_sin; int /*<<< orphan*/ * rf_fwd; int /*<<< orphan*/  rf_oldid; } ;
typedef  TYPE_5__ rpc_forward ;
typedef  int /*<<< orphan*/  opaque_t ;
typedef  int /*<<< orphan*/  fwd_fun ;
typedef  int /*<<< orphan*/  dq ;

/* Variables and functions */
 int AM_ERRNO_HOST_DOWN ; 
 int ENOBUFS ; 
 int ENOENT ; 
 scalar_t__ Finishing ; 
 int MK_RPC_XID (int,int /*<<< orphan*/ ) ; 
 int RPC_XID_MASK ; 
#define  RPC_XID_MOUNTD 131 
#define  RPC_XID_NFSPING 130 
#define  RPC_XID_PORTMAP 129 
#define  RPC_XID_WEBNFS 128 
 int /*<<< orphan*/  XID_ALLOC () ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 scalar_t__ amd_state ; 
 int /*<<< orphan*/  dlog (char*,...) ; 
 int errno ; 
 TYPE_5__* fwd_alloc () ; 
 int /*<<< orphan*/  fwd_free (TYPE_5__*) ; 
 TYPE_5__* fwd_locate (int) ; 
 int /*<<< orphan*/  fwd_sock ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  inet_dquad (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  t_errno ; 
 scalar_t__ t_sndudata (int /*<<< orphan*/ ,struct t_unitdata*) ; 

int
fwd_packet(int type_id, char *pkt, int len, struct sockaddr_in *fwdto, struct sockaddr_in *replyto, opaque_t cb_arg, fwd_fun *cb)
{
  rpc_forward *p;
  u_int *pkt_int;
  int error;
#ifdef HAVE_TRANSPORT_TYPE_TLI
  struct t_unitdata ud;
#endif /* HAVE_TRANSPORT_TYPE_TLI */

  if ((int) amd_state >= (int) Finishing)
    return ENOENT;

  /*
   * See if the type_id is fully specified.
   * If so, then discard any old entries
   * for this id.
   * Otherwise make sure the type_id is
   * fully qualified by allocating an id here.
   */
  switch (type_id & RPC_XID_MASK) {
  case RPC_XID_PORTMAP:
    dlog("Sending PORTMAP request %#x", type_id);
    break;
  case RPC_XID_MOUNTD:
    dlog("Sending MOUNTD request %#x", type_id);
    break;
  case RPC_XID_NFSPING:
    dlog("Sending NFS ping %#x", type_id);
    break;
  case RPC_XID_WEBNFS:
    dlog("Sending WebNFS lookup %#x", type_id);
    break;
  default:
    dlog("UNKNOWN RPC XID %#x", type_id);
    break;
  }

  if (type_id & ~RPC_XID_MASK) {
    p = fwd_locate(type_id);
    if (p) {
      dlog("Discarding earlier rpc fwd handle");
      fwd_free(p);
    }
  } else {
    dlog("Allocating a new xid...");
    type_id = MK_RPC_XID(type_id, XID_ALLOC());
  }

  p = fwd_alloc();
  if (!p)
    return ENOBUFS;

  error = 0;

  pkt_int = (u_int *) pkt;

  /*
   * Get the original packet id
   */
  p->rf_oldid = ntohl(*pkt_int);

  /*
   * Replace with newly allocated id
   */
  p->rf_xid = type_id;
  *pkt_int = htonl(type_id);

  /*
   * The sendto may fail if, for example, the route
   * to a remote host is lost because an intermediate
   * gateway has gone down.  Important to fill in the
   * rest of "p" otherwise nasty things happen later...
   */
#ifdef DEBUG
  {
    char dq[20];
    if (p && fwdto)
      dlog("Sending packet id %#x to %s:%d",
	   p->rf_xid,
	   inet_dquad(dq, sizeof(dq), fwdto->sin_addr.s_addr),
	   ntohs(fwdto->sin_port));
  }
#endif /* DEBUG */

  /* if NULL, remote server probably down */
  if (!fwdto) {
    error = AM_ERRNO_HOST_DOWN;
    goto out;
  }

#ifdef HAVE_TRANSPORT_TYPE_TLI
  ud.addr.buf = (char *) fwdto;
  if (fwdto)			/* if NULL, set sizes to zero */
    ud.addr.maxlen = ud.addr.len = sizeof(struct sockaddr_in);
  else
    ud.addr.maxlen = ud.addr.len = 0;
  ud.opt.buf = (char *) NULL;
  ud.opt.maxlen = ud.opt.len = 0;
  ud.udata.buf = pkt;
  ud.udata.maxlen = ud.udata.len = len;
  if (t_sndudata(fwd_sock, &ud) < 0) {
    plog(XLOG_ERROR,"fwd_packet failed: t_errno=%d, errno=%d",t_errno,errno);
    error = errno;
  }
#else /* not HAVE_TRANSPORT_TYPE_TLI */
  if (sendto(fwd_sock, (char *) pkt, len, 0,
	     (struct sockaddr *) fwdto, sizeof(*fwdto)) < 0)
    error = errno;
#endif /* not HAVE_TRANSPORT_TYPE_TLI */

  /*
   * Save callback function and return address
   */
out:
  p->rf_fwd = cb;
  if (replyto)
    p->rf_sin = *replyto;
  else
    memset((voidp) &p->rf_sin, 0, sizeof(p->rf_sin));
  p->rf_ptr = cb_arg;

  return error;
}