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
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_2__ addr; TYPE_1__ param_hdr; } ;
union sctp_addr_param {TYPE_3__ v4; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_10__ {TYPE_4__ sin_addr; } ;
union sctp_addr {TYPE_5__ v4; } ;
typedef  int /*<<< orphan*/  sctp_ipv4addr_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_PARAM_IPV4_ADDRESS ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static int sctp_v4_to_addr_param(const union sctp_addr *addr,
				 union sctp_addr_param *param)
{
	int length = sizeof(sctp_ipv4addr_param_t);

	param->v4.param_hdr.type = SCTP_PARAM_IPV4_ADDRESS;
	param->v4.param_hdr.length = htons(length);
	param->v4.addr.s_addr = addr->v4.sin_addr.s_addr;

	return length;
}