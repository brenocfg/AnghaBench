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
union pf_state_xport {int /*<<< orphan*/  port; int /*<<< orphan*/  spi; int /*<<< orphan*/  call_id; } ;
struct TYPE_2__ {int /*<<< orphan*/ * port; int /*<<< orphan*/  op; } ;
union pf_rule_xport {TYPE_1__ range; int /*<<< orphan*/  spi; int /*<<< orphan*/  call_id; } ;
typedef  int u_int8_t ;

/* Variables and functions */
#define  IPPROTO_ESP 133 
#define  IPPROTO_GRE 132 
#define  IPPROTO_ICMP 131 
#define  IPPROTO_ICMPV6 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int PF_GRE_PPTP_VARIANT ; 
 int pf_match_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pf_match_xport(u_int8_t proto, u_int8_t proto_variant, union pf_rule_xport *rx,
    union pf_state_xport *sx)
{
	int d = !0;

	if (sx) {
		switch (proto) {
		case IPPROTO_GRE:
			if (proto_variant == PF_GRE_PPTP_VARIANT)
				d = (rx->call_id == sx->call_id);
			break;

		case IPPROTO_ESP:
			d = (rx->spi == sx->spi);
			break;

		case IPPROTO_TCP:
		case IPPROTO_UDP:
		case IPPROTO_ICMP:
		case IPPROTO_ICMPV6:
			if (rx->range.op)
				d = pf_match_port(rx->range.op,
				    rx->range.port[0], rx->range.port[1],
				    sx->port);
			break;

		default:
			break;
		}
	}

	return (d);
}