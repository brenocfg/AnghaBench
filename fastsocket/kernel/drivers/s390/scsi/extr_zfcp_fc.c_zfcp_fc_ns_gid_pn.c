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
struct zfcp_port {struct zfcp_adapter* adapter; } ;
struct zfcp_gid_pn_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  gid_pn_data; } ;
struct zfcp_adapter {TYPE_1__ pool; TYPE_2__* gs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct zfcp_gid_pn_data* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct zfcp_gid_pn_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct zfcp_gid_pn_data*,int /*<<< orphan*/ ,int) ; 
 int zfcp_fc_ns_gid_pn_request (struct zfcp_port*,struct zfcp_gid_pn_data*) ; 
 int zfcp_fc_wka_port_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fc_wka_port_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zfcp_fc_ns_gid_pn(struct zfcp_port *port)
{
	int ret;
	struct zfcp_gid_pn_data *gid_pn;
	struct zfcp_adapter *adapter = port->adapter;

	gid_pn = mempool_alloc(adapter->pool.gid_pn_data, GFP_ATOMIC);
	if (!gid_pn)
		return -ENOMEM;

	memset(gid_pn, 0, sizeof(*gid_pn));

	ret = zfcp_fc_wka_port_get(&adapter->gs->ds);
	if (ret)
		goto out;

	ret = zfcp_fc_ns_gid_pn_request(port, gid_pn);

	zfcp_fc_wka_port_put(&adapter->gs->ds);
out:
	mempool_free(gid_pn, adapter->pool.gid_pn_data);
	return ret;
}