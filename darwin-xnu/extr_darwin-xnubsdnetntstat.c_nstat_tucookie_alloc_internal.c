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
struct nstat_tucookie {int /*<<< orphan*/  pname; struct inpcb* inp; } ;
struct inpcb {int /*<<< orphan*/  inp_nstat_refcnt; TYPE_1__* inp_socket; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_pid; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  OSFree (struct nstat_tucookie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 struct nstat_tucookie* OSMalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_PROTO (TYPE_1__*) ; 
 int /*<<< orphan*/  WNT_ACQUIRE ; 
 scalar_t__ WNT_STOPUSING ; 
 int /*<<< orphan*/  bzero (struct nstat_tucookie*,int) ; 
 scalar_t__ in_pcb_checkstate (struct inpcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nstat_malloc_tag ; 
 int /*<<< orphan*/  nstat_mtx ; 
 int /*<<< orphan*/  proc_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct nstat_tucookie *
nstat_tucookie_alloc_internal(
    struct inpcb *inp,
    bool	  ref,
    bool	  locked)
{
	struct nstat_tucookie *cookie;

	cookie = OSMalloc(sizeof(*cookie), nstat_malloc_tag);
	if (cookie == NULL)
		return NULL;
	if (!locked)
		LCK_MTX_ASSERT(&nstat_mtx, LCK_MTX_ASSERT_NOTOWNED);
	if (ref && in_pcb_checkstate(inp, WNT_ACQUIRE, locked) == WNT_STOPUSING)
	{
		OSFree(cookie, sizeof(*cookie), nstat_malloc_tag);
		return NULL;
	}
	bzero(cookie, sizeof(*cookie));
	cookie->inp = inp;
	proc_name(inp->inp_socket->last_pid, cookie->pname,
	    sizeof(cookie->pname));
	/*
	 * We only increment the reference count for UDP sockets because we
	 * only cache UDP socket tuples.
	 */
	if (SOCK_PROTO(inp->inp_socket) == IPPROTO_UDP)
		OSIncrementAtomic(&inp->inp_nstat_refcnt);

	return cookie;
}