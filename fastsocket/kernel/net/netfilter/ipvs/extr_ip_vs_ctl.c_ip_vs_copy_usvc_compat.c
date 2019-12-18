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
struct TYPE_2__ {int /*<<< orphan*/  ip; } ;
struct ip_vs_service_user_kern {int /*<<< orphan*/  netmask; int /*<<< orphan*/  timeout; int /*<<< orphan*/  flags; int /*<<< orphan*/  sched_name; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  port; TYPE_1__ addr; int /*<<< orphan*/  protocol; int /*<<< orphan*/  af; } ;
struct ip_vs_service_user {int /*<<< orphan*/  netmask; int /*<<< orphan*/  timeout; int /*<<< orphan*/  flags; int /*<<< orphan*/  sched_name; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  memset (struct ip_vs_service_user_kern*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ip_vs_copy_usvc_compat(struct ip_vs_service_user_kern *usvc,
				  struct ip_vs_service_user *usvc_compat)
{
	memset(usvc, 0, sizeof(*usvc));

	usvc->af		= AF_INET;
	usvc->protocol		= usvc_compat->protocol;
	usvc->addr.ip		= usvc_compat->addr;
	usvc->port		= usvc_compat->port;
	usvc->fwmark		= usvc_compat->fwmark;

	/* Deep copy of sched_name is not needed here */
	usvc->sched_name	= usvc_compat->sched_name;

	usvc->flags		= usvc_compat->flags;
	usvc->timeout		= usvc_compat->timeout;
	usvc->netmask		= usvc_compat->netmask;
}