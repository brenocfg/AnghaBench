#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; TYPE_1__ param_hdr; } ;
union sctp_addr_param {TYPE_2__ v6; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;
union sctp_addr {TYPE_3__ v6; } ;
typedef  int /*<<< orphan*/  sctp_ipv6addr_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_PARAM_IPV6_ADDRESS ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sctp_v6_to_addr_param(const union sctp_addr *addr,
				 union sctp_addr_param *param)
{
	int length = sizeof(sctp_ipv6addr_param_t);

	param->v6.param_hdr.type = SCTP_PARAM_IPV6_ADDRESS;
	param->v6.param_hdr.length = htons(length);
	ipv6_addr_copy(&param->v6.addr, &addr->v6.sin6_addr);

	return length;
}