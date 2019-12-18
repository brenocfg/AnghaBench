#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fd; int /*<<< orphan*/  dev; scalar_t__ fixed_config; } ;
struct TYPE_6__ {TYPE_4__ tuntap; } ;
struct TYPE_7__ {TYPE_2__ info; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_name; } ;
struct iss_net_private {TYPE_3__ tp; TYPE_1__ host; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_addr ; 
 int /*<<< orphan*/  iter_addresses (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simc_close (int) ; 

__attribute__((used)) static void tuntap_close(struct iss_net_private *lp)
{
#if 0
	if (lp->tp.info.tuntap.fixed_config)
		iter_addresses(lp->tp.info.tuntap.dev, close_addr, lp->host.dev_name);
#endif
	simc_close(lp->tp.info.tuntap.fd);
	lp->tp.info.tuntap.fd = -1;
}