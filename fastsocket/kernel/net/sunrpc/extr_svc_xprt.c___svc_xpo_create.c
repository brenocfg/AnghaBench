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
struct svc_xprt_class {TYPE_1__* xcl_ops; } ;
struct svc_xprt {int dummy; } ;
struct svc_serv {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  sin6 ;
typedef  int /*<<< orphan*/  sin ;
struct TYPE_3__ {struct svc_xprt* (* xpo_create ) (struct svc_serv*,struct net*,struct sockaddr*,size_t,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 struct svc_xprt* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN6ADDR_ANY_INIT ; 
 int /*<<< orphan*/  INADDR_ANY ; 
#define  PF_INET 129 
#define  PF_INET6 128 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (unsigned short const) ; 
 struct svc_xprt* stub1 (struct svc_serv*,struct net*,struct sockaddr*,size_t,int) ; 

__attribute__((used)) static struct svc_xprt *__svc_xpo_create(struct svc_xprt_class *xcl,
					 struct svc_serv *serv,
					 struct net *net,
					 const int family,
					 const unsigned short port,
					 int flags)
{
	struct sockaddr_in sin = {
		.sin_family		= AF_INET,
		.sin_addr.s_addr	= htonl(INADDR_ANY),
		.sin_port		= htons(port),
	};
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	struct sockaddr_in6 sin6 = {
		.sin6_family		= AF_INET6,
		.sin6_addr		= IN6ADDR_ANY_INIT,
		.sin6_port		= htons(port),
	};
#endif	/* defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE) */
	struct sockaddr *sap;
	size_t len;

	switch (family) {
	case PF_INET:
		sap = (struct sockaddr *)&sin;
		len = sizeof(sin);
		break;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case PF_INET6:
		sap = (struct sockaddr *)&sin6;
		len = sizeof(sin6);
		break;
#endif	/* defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE) */
	default:
		return ERR_PTR(-EAFNOSUPPORT);
	}

	return xcl->xcl_ops->xpo_create(serv, net, sap, len, flags);
}