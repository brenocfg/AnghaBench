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
struct TYPE_3__ {int /*<<< orphan*/  fu_divert_port; } ;
struct ip6_fw_32 {int /*<<< orphan*/  fw_nports; int /*<<< orphan*/  fw_prot; TYPE_1__ fw_un; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  fw_out_if; int /*<<< orphan*/  fw_in_if; int /*<<< orphan*/  fw_icmp6types; int /*<<< orphan*/  fw_tcpnf; int /*<<< orphan*/  fw_tcpf; int /*<<< orphan*/  fw_ip6nopt; int /*<<< orphan*/  fw_ip6opt; int /*<<< orphan*/  fw_pts; int /*<<< orphan*/  fw_ipflg; int /*<<< orphan*/  fw_flg; int /*<<< orphan*/  fw_number; int /*<<< orphan*/  fw_dmsk; int /*<<< orphan*/  fw_smsk; int /*<<< orphan*/  fw_dst; int /*<<< orphan*/  fw_src; int /*<<< orphan*/  fw_bcnt; int /*<<< orphan*/  fw_pcnt; int /*<<< orphan*/  context; int /*<<< orphan*/  version; } ;
struct TYPE_4__ {int /*<<< orphan*/  fu_divert_port; } ;
struct ip6_fw {int /*<<< orphan*/  fw_nports; int /*<<< orphan*/  fw_prot; TYPE_2__ fw_un; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  fw_out_if; int /*<<< orphan*/  fw_in_if; int /*<<< orphan*/  fw_icmp6types; int /*<<< orphan*/  fw_tcpnf; int /*<<< orphan*/  fw_tcpf; int /*<<< orphan*/  fw_ip6nopt; int /*<<< orphan*/  fw_ip6opt; int /*<<< orphan*/  fw_pts; int /*<<< orphan*/  fw_ipflg; int /*<<< orphan*/  fw_flg; int /*<<< orphan*/  fw_number; int /*<<< orphan*/  fw_dmsk; int /*<<< orphan*/  fw_smsk; int /*<<< orphan*/  fw_dst; int /*<<< orphan*/  fw_src; int /*<<< orphan*/  fw_bcnt; int /*<<< orphan*/  fw_pcnt; int /*<<< orphan*/  context; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_DOWN_EXPLICIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IPV6_FW_MAX_PORTS ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  user32_addr_t ; 

__attribute__((used)) static void
cp_to_user_32( struct ip6_fw_32 *userrule_32, struct ip6_fw *rule)
{
	userrule_32->version = rule->version;
	userrule_32->context = CAST_DOWN_EXPLICIT( user32_addr_t, rule->context);
	userrule_32->fw_pcnt = rule->fw_pcnt;
	userrule_32->fw_bcnt = rule->fw_bcnt;
	userrule_32->fw_src = rule->fw_src;
	userrule_32->fw_dst = rule->fw_dst;
	userrule_32->fw_smsk = rule->fw_smsk;
	userrule_32->fw_dmsk = rule->fw_dmsk;
	userrule_32->fw_number = rule->fw_number;
	userrule_32->fw_flg = rule->fw_flg;
	userrule_32->fw_ipflg = rule->fw_ipflg;
	bcopy( rule->fw_pts, userrule_32->fw_pts, IPV6_FW_MAX_PORTS);
	userrule_32->fw_ip6opt = rule->fw_ip6opt ;
	userrule_32->fw_ip6nopt = rule->fw_ip6nopt;
	userrule_32->fw_tcpf = rule->fw_tcpf;
	userrule_32->fw_tcpnf = rule->fw_tcpnf;
	bcopy( rule->fw_icmp6types, userrule_32->fw_icmp6types, sizeof(rule->fw_icmp6types));
	userrule_32->fw_in_if = rule->fw_in_if;
	userrule_32->fw_out_if = rule->fw_out_if;
	userrule_32->timestamp = rule->timestamp;
	userrule_32->fw_un.fu_divert_port = rule->fw_un.fu_divert_port;
	userrule_32->fw_prot = rule->fw_prot;
	userrule_32->fw_nports = rule->fw_nports;
}