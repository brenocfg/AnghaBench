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
struct ipx_interface {int /*<<< orphan*/  if_netnum; } ;

/* Variables and functions */
 int ipxrtr_add_route (int /*<<< orphan*/ ,struct ipx_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipxitf_add_local_route(struct ipx_interface *intrfc)
{
	return ipxrtr_add_route(intrfc->if_netnum, intrfc, NULL);
}