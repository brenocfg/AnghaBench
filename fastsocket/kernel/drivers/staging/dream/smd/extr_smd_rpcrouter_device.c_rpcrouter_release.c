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
struct msm_rpc_endpoint {int dummy; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int msm_rpcrouter_destroy_local_endpoint (struct msm_rpc_endpoint*) ; 

__attribute__((used)) static int rpcrouter_release(struct inode *inode, struct file *filp)
{
	struct msm_rpc_endpoint *ept;
	ept = (struct msm_rpc_endpoint *) filp->private_data;

	return msm_rpcrouter_destroy_local_endpoint(ept);
}