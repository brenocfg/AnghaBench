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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct rpc_create_args {int addrsize; char* servername; int /*<<< orphan*/  flags; int /*<<< orphan*/  authflavor; int /*<<< orphan*/  version; int /*<<< orphan*/ * program; struct sockaddr* address; int /*<<< orphan*/  protocol; int /*<<< orphan*/ * net; } ;
struct rpc_clnt {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  NSM_VERSION ; 
 int /*<<< orphan*/  RPC_AUTH_NULL ; 
 int /*<<< orphan*/  RPC_CLNT_CREATE_NOPING ; 
 int /*<<< orphan*/  XPRT_TRANSPORT_UDP ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  nsm_program ; 
 struct rpc_clnt* rpc_create (struct rpc_create_args*) ; 

__attribute__((used)) static struct rpc_clnt *nsm_create(void)
{
	struct sockaddr_in sin = {
		.sin_family		= AF_INET,
		.sin_addr.s_addr	= htonl(INADDR_LOOPBACK),
	};
	struct rpc_create_args args = {
		.net			= &init_net,
		.protocol		= XPRT_TRANSPORT_UDP,
		.address		= (struct sockaddr *)&sin,
		.addrsize		= sizeof(sin),
		.servername		= "rpc.statd",
		.program		= &nsm_program,
		.version		= NSM_VERSION,
		.authflavor		= RPC_AUTH_NULL,
		.flags			= RPC_CLNT_CREATE_NOPING,
	};

	return rpc_create(&args);
}