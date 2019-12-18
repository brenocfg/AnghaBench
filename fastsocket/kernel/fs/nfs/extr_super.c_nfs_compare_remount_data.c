#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct nfs_server {scalar_t__ flags; scalar_t__ rsize; scalar_t__ wsize; unsigned int acregmin; unsigned int acregmax; unsigned int acdirmin; unsigned int acdirmax; scalar_t__ port; TYPE_5__* nfs_client; TYPE_3__* client; } ;
struct TYPE_9__ {scalar_t__ port; scalar_t__ addrlen; int /*<<< orphan*/  address; } ;
struct nfs_parsed_mount_data {scalar_t__ flags; scalar_t__ rsize; scalar_t__ wsize; scalar_t__ retrans; scalar_t__* auth_flavors; unsigned int acregmin; unsigned int acregmax; unsigned int acdirmin; unsigned int acdirmax; unsigned int timeo; TYPE_4__ nfs_server; } ;
struct TYPE_10__ {scalar_t__ cl_addrlen; int /*<<< orphan*/  cl_addr; } ;
struct TYPE_8__ {TYPE_2__* cl_timeout; TYPE_1__* cl_auth; } ;
struct TYPE_7__ {scalar_t__ to_retries; unsigned int to_initval; } ;
struct TYPE_6__ {scalar_t__ au_flavor; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int HZ ; 
 int /*<<< orphan*/  rpc_cmp_addr (struct sockaddr*,struct sockaddr*) ; 

__attribute__((used)) static int
nfs_compare_remount_data(struct nfs_server *nfss,
			 struct nfs_parsed_mount_data *data)
{
	if (data->flags != nfss->flags ||
	    data->rsize != nfss->rsize ||
	    data->wsize != nfss->wsize ||
	    data->retrans != nfss->client->cl_timeout->to_retries ||
	    data->auth_flavors[0] != nfss->client->cl_auth->au_flavor ||
	    data->acregmin != nfss->acregmin / HZ ||
	    data->acregmax != nfss->acregmax / HZ ||
	    data->acdirmin != nfss->acdirmin / HZ ||
	    data->acdirmax != nfss->acdirmax / HZ ||
	    data->timeo != (10U * nfss->client->cl_timeout->to_initval / HZ) ||
	    data->nfs_server.port != nfss->port ||
	    data->nfs_server.addrlen != nfss->nfs_client->cl_addrlen ||
	    !rpc_cmp_addr((struct sockaddr *)&data->nfs_server.address,
			  (struct sockaddr *)&nfss->nfs_client->cl_addr))
		return -EINVAL;

	return 0;
}