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
struct ip_vs_protocol {int /*<<< orphan*/  timeout_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_SCTP_S_LAST ; 
 int ip_vs_set_state_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sctp_state_name_table ; 

__attribute__((used)) static int
sctp_set_state_timeout(struct ip_vs_protocol *pp, char *sname, int to)
{

return ip_vs_set_state_timeout(pp->timeout_table, IP_VS_SCTP_S_LAST,
				sctp_state_name_table, sname, to);
}