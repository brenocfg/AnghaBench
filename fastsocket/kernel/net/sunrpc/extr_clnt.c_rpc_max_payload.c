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
struct rpc_clnt {TYPE_1__* cl_xprt; } ;
struct TYPE_2__ {size_t max_payload; } ;

/* Variables and functions */

size_t rpc_max_payload(struct rpc_clnt *clnt)
{
	return clnt->cl_xprt->max_payload;
}