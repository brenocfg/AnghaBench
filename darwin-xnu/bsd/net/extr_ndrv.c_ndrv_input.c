#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/  so_rcv; } ;
struct sockaddr_dl {int sdl_len; int sdl_alen; int /*<<< orphan*/  sdl_data; scalar_t__ sdl_slen; scalar_t__ sdl_nlen; int /*<<< orphan*/  sdl_type; scalar_t__ sdl_index; int /*<<< orphan*/  sdl_family; } ;
struct sockaddr {int dummy; } ;
struct ndrv_cb {struct socket* nd_socket; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  TYPE_1__* mbuf_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_8__ {int /*<<< orphan*/  dom_mtx; } ;
struct TYPE_7__ {int /*<<< orphan*/ * m_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NDRV ; 
 int /*<<< orphan*/  EJUSTRETURN ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ *,int) ; 
 int ifnet_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 TYPE_1__* m_prepend (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct ndrv_cb* ndrv_find_inbound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ndrvdomain ; 
 scalar_t__ sbappendaddr (int /*<<< orphan*/ *,struct sockaddr*,TYPE_1__*,struct mbuf*,int*) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 

__attribute__((used)) static errno_t
ndrv_input(
	ifnet_t				ifp,
	protocol_family_t	proto_family,
	mbuf_t				m,
	char				*frame_header)
{
	struct socket *so;
	struct sockaddr_dl ndrvsrc;
	struct ndrv_cb *np;
	int error = 0;

    ndrvsrc.sdl_len = sizeof (struct sockaddr_dl);
    ndrvsrc.sdl_family = AF_NDRV;
    ndrvsrc.sdl_index = 0;

    /* move packet from if queue to socket */
	/* Should be media-independent */
    ndrvsrc.sdl_type = IFT_ETHER;
    ndrvsrc.sdl_nlen = 0;
    ndrvsrc.sdl_alen = 6;
    ndrvsrc.sdl_slen = 0;
    bcopy(frame_header, &ndrvsrc.sdl_data, 6);

	np = ndrv_find_inbound(ifp, proto_family);
	if (np == NULL)
	{
		return(ENOENT);
	}
	so = np->nd_socket;
    /* prepend the frame header */
    m = m_prepend(m, ifnet_hdrlen(ifp), M_NOWAIT);
    if (m == NULL)
        return EJUSTRETURN;
    bcopy(frame_header, m->m_data, ifnet_hdrlen(ifp));

	LCK_MTX_ASSERT(ndrvdomain->dom_mtx, LCK_MTX_ASSERT_NOTOWNED);
	lck_mtx_lock(ndrvdomain->dom_mtx);
	if (sbappendaddr(&(so->so_rcv), (struct sockaddr *)&ndrvsrc,
			 		 m, (struct mbuf *)0, &error) != 0) {
		sorwakeup(so);
	}
	lck_mtx_unlock(ndrvdomain->dom_mtx);
	return 0; /* radar 4030377 - always return 0 */
}