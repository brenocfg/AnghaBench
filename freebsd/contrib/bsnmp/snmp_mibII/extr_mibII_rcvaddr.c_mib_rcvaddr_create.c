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
typedef  size_t u_int ;
typedef  size_t u_char ;
struct TYPE_2__ {size_t len; size_t* subs; } ;
struct mibrcvaddr {size_t ifindex; size_t addrlen; TYPE_1__ index; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct mibif {size_t index; } ;

/* Variables and functions */
 scalar_t__ ASN_MAXOIDLEN ; 
 int /*<<< orphan*/  INSERT_OBJECT_OID (struct mibrcvaddr*,int /*<<< orphan*/ *) ; 
 scalar_t__ OIDLEN_ifRcvAddressEntry ; 
 struct mibrcvaddr* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t const*,size_t) ; 
 int /*<<< orphan*/  mibrcvaddr_list ; 

struct mibrcvaddr *
mib_rcvaddr_create(struct mibif *ifp, const u_char *addr, size_t addrlen)
{
	struct mibrcvaddr *rcv;
	u_int i;

	if (addrlen + OIDLEN_ifRcvAddressEntry + 1 > ASN_MAXOIDLEN)
		return (NULL);

	if ((rcv = malloc(sizeof(*rcv))) == NULL)
		return (NULL);
	rcv->ifindex = ifp->index;
	rcv->addrlen = addrlen;
	memcpy(rcv->addr, addr, addrlen);
	rcv->flags = 0;

	rcv->index.len = addrlen + 2;
	rcv->index.subs[0] = ifp->index;
	rcv->index.subs[1] = addrlen;
	for (i = 0; i < addrlen; i++)
		rcv->index.subs[i + 2] = addr[i];

	INSERT_OBJECT_OID(rcv, &mibrcvaddr_list);

	return (rcv);
}