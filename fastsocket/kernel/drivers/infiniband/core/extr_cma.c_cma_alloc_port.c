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
struct rdma_id_private {int dummy; } ;
struct rdma_bind_list {unsigned short port; struct idr* ps; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cma_bind_port (struct rdma_bind_list*,struct rdma_id_private*) ; 
 int idr_get_new_above (struct idr*,struct rdma_bind_list*,unsigned short,int*) ; 
 scalar_t__ idr_pre_get (struct idr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (struct idr*,int) ; 
 int /*<<< orphan*/  kfree (struct rdma_bind_list*) ; 
 struct rdma_bind_list* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cma_alloc_port(struct idr *ps, struct rdma_id_private *id_priv,
			  unsigned short snum)
{
	struct rdma_bind_list *bind_list;
	int port, ret;

	bind_list = kzalloc(sizeof *bind_list, GFP_KERNEL);
	if (!bind_list)
		return -ENOMEM;

	do {
		ret = idr_get_new_above(ps, bind_list, snum, &port);
	} while ((ret == -EAGAIN) && idr_pre_get(ps, GFP_KERNEL));

	if (ret)
		goto err1;

	if (port != snum) {
		ret = -EADDRNOTAVAIL;
		goto err2;
	}

	bind_list->ps = ps;
	bind_list->port = (unsigned short) port;
	cma_bind_port(bind_list, id_priv);
	return 0;
err2:
	idr_remove(ps, port);
err1:
	kfree(bind_list);
	return ret;
}