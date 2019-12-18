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
struct nlattr {int dummy; } ;
struct ip_vs_service_user_kern {int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  protocol; int /*<<< orphan*/  af; scalar_t__ fwmark; } ;
struct ip_vs_service {int dummy; } ;

/* Variables and functions */
 struct ip_vs_service* ERR_PTR (int) ; 
 struct ip_vs_service* __ip_vs_service_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ip_vs_service* __ip_vs_svc_fwm_get (int /*<<< orphan*/ ,scalar_t__) ; 
 int ip_vs_genl_parse_service (struct ip_vs_service_user_kern*,struct nlattr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ip_vs_service *ip_vs_genl_find_service(struct nlattr *nla)
{
	struct ip_vs_service_user_kern usvc;
	int ret;

	ret = ip_vs_genl_parse_service(&usvc, nla, 0);
	if (ret)
		return ERR_PTR(ret);

	if (usvc.fwmark)
		return __ip_vs_svc_fwm_get(usvc.af, usvc.fwmark);
	else
		return __ip_vs_service_get(usvc.af, usvc.protocol,
					   &usvc.addr, usvc.port);
}