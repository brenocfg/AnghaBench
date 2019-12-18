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
typedef  int /*<<< orphan*/  uint32_t ;
struct rpcrouter_ioctl_server_args {int /*<<< orphan*/  vers; int /*<<< orphan*/  prog; } ;
struct msm_rpc_endpoint {int dummy; } ;
struct file {scalar_t__ private_data; } ;
typedef  int /*<<< orphan*/  server_args ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MSM_RPC_GET_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCROUTER_MSGSIZE_MAX ; 
#define  RPC_ROUTER_IOCTL_GET_MINOR_VERSION 132 
#define  RPC_ROUTER_IOCTL_GET_MTU 131 
#define  RPC_ROUTER_IOCTL_GET_VERSION 130 
#define  RPC_ROUTER_IOCTL_REGISTER_SERVER 129 
#define  RPC_ROUTER_IOCTL_UNREGISTER_SERVER 128 
 int /*<<< orphan*/  RPC_ROUTER_VERSION_V1 ; 
 int copy_from_user (struct rpcrouter_ioctl_server_args*,void*,int) ; 
 int /*<<< orphan*/  msm_rpc_get_vers (struct msm_rpc_endpoint*) ; 
 int /*<<< orphan*/  msm_rpc_register_server (struct msm_rpc_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_rpc_unregister_server (struct msm_rpc_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int put_user (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static long rpcrouter_ioctl(struct file *filp, unsigned int cmd,
			    unsigned long arg)
{
	struct msm_rpc_endpoint *ept;
	struct rpcrouter_ioctl_server_args server_args;
	int rc = 0;
	uint32_t n;

	ept = (struct msm_rpc_endpoint *) filp->private_data;
	switch (cmd) {

	case RPC_ROUTER_IOCTL_GET_VERSION:
		n = RPC_ROUTER_VERSION_V1;
		rc = put_user(n, (unsigned int *) arg);
		break;

	case RPC_ROUTER_IOCTL_GET_MTU:
		/* the pacmark word reduces the actual payload
		 * possible per message
		 */
		n = RPCROUTER_MSGSIZE_MAX - sizeof(uint32_t);
		rc = put_user(n, (unsigned int *) arg);
		break;

	case RPC_ROUTER_IOCTL_REGISTER_SERVER:
		rc = copy_from_user(&server_args, (void *) arg,
				    sizeof(server_args));
		if (rc < 0)
			break;
		msm_rpc_register_server(ept,
					server_args.prog,
					server_args.vers);
		break;

	case RPC_ROUTER_IOCTL_UNREGISTER_SERVER:
		rc = copy_from_user(&server_args, (void *) arg,
				    sizeof(server_args));
		if (rc < 0)
			break;

		msm_rpc_unregister_server(ept,
					  server_args.prog,
					  server_args.vers);
		break;

	case RPC_ROUTER_IOCTL_GET_MINOR_VERSION:
		n = MSM_RPC_GET_MINOR(msm_rpc_get_vers(ept));
		rc = put_user(n, (unsigned int *)arg);
		break;

	default:
		rc = -EINVAL;
		break;
	}

	return rc;
}