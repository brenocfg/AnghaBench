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
 int /*<<< orphan*/  IP_VS_INIT_HASH_TABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_apps ; 
 int /*<<< orphan*/  tcp_timeouts ; 

__attribute__((used)) static void ip_vs_tcp_init(struct ip_vs_protocol *pp)
{
	IP_VS_INIT_HASH_TABLE(tcp_apps);
	pp->timeout_table = tcp_timeouts;
}