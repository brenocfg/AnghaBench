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
struct TYPE_10__ {scalar_t__ dst; scalar_t__ src; } ;
struct TYPE_9__ {TYPE_5__ tp; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_6__ {scalar_t__ dst; scalar_t__ src; } ;
struct TYPE_7__ {TYPE_1__ tp; } ;
struct sw_flow_key {TYPE_4__ ipv6; TYPE_3__ eth; TYPE_2__ ipv4; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_tp_port(const struct sw_flow_key *flow_key)
{
	if (flow_key->eth.type == htons(ETH_P_IP)) {
		if (flow_key->ipv4.tp.src || flow_key->ipv4.tp.dst)
			return 0;
	} else if (flow_key->eth.type == htons(ETH_P_IPV6)) {
		if (flow_key->ipv6.tp.src || flow_key->ipv6.tp.dst)
			return 0;
	}

	return -EINVAL;
}