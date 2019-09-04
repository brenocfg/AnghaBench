#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  void* u_int16_t ;
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr_in {void* sin_port; } ;
typedef  int /*<<< orphan*/  mbuf_t ;

/* Variables and functions */
 int EPROGUNAVAIL ; 
 int /*<<< orphan*/  MBUF_TYPE_DATA ; 
 int /*<<< orphan*/  MBUF_WAITOK ; 
 int /*<<< orphan*/  PMAPPORT ; 
 int /*<<< orphan*/  PMAPPROC_GETPORT ; 
 scalar_t__ PMAPPROG ; 
 int /*<<< orphan*/  PMAPVERS ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 void* htonl (scalar_t__) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int krpc_call (struct sockaddr_in*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* mbuf_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ ) ; 
 int mbuf_gethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_pkthdr_setlen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mbuf_setlen (int /*<<< orphan*/ ,int) ; 

int
krpc_portmap(
	struct sockaddr_in *sin,	/* server address */
	u_int prog, u_int vers, u_int proto,	/* host order */
	u_int16_t *portp)		/* network order */
{
	struct sdata {
		u_int32_t prog;		/* call program */
		u_int32_t vers;		/* call version */
		u_int32_t proto;	/* call protocol */
		u_int32_t port;		/* call port (unused) */
	} *sdata;
	struct rdata {
		u_int16_t pad;
		u_int16_t port;
	} *rdata;
	mbuf_t m;
	int error;

	/* The portmapper port is fixed. */
	if (prog == PMAPPROG) {
		*portp = htons(PMAPPORT);
		return 0;
	}

	error = mbuf_gethdr(MBUF_WAITOK, MBUF_TYPE_DATA, &m);
	if (error)
		return error;
	mbuf_setlen(m, sizeof(*sdata));
	mbuf_pkthdr_setlen(m, sizeof(*sdata));
	sdata = mbuf_data(m);

	/* Do the RPC to get it. */
	sdata->prog = htonl(prog);
	sdata->vers = htonl(vers);
	sdata->proto = htonl(proto);
	sdata->port = 0;

	sin->sin_port = htons(PMAPPORT);
	error = krpc_call(sin, SOCK_DGRAM, PMAPPROG, PMAPVERS, PMAPPROC_GETPORT, &m, NULL);
	if (error) 
		return error;

	rdata = mbuf_data(m);

	if (mbuf_len(m) >= sizeof(*rdata)) {
		*portp = rdata->port;
	}

	if (mbuf_len(m) < sizeof(*rdata) || !rdata->port)
		error = EPROGUNAVAIL;

	mbuf_freem(m);
	return (error);
}