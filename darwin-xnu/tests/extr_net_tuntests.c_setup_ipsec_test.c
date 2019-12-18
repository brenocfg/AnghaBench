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

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_CONTROL_NAME ; 
 int /*<<< orphan*/  IPSEC_OPT_ENABLE_CHANNEL ; 
 int /*<<< orphan*/  IPSEC_OPT_ENABLE_FLOWSWITCH ; 
 int /*<<< orphan*/  IPSEC_OPT_ENABLE_NETIF ; 
 int /*<<< orphan*/  IPSEC_OPT_GET_CHANNEL_UUID ; 
 int /*<<< orphan*/  IPSEC_OPT_IFNAME ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  g_CONTROL_NAME ; 
 int /*<<< orphan*/  g_OPT_ENABLE_CHANNEL ; 
 int /*<<< orphan*/  g_OPT_ENABLE_FLOWSWITCH ; 
 int /*<<< orphan*/  g_OPT_ENABLE_NETIF ; 
 int /*<<< orphan*/  g_OPT_GET_CHANNEL_UUID ; 
 int /*<<< orphan*/  g_OPT_IFNAME ; 
 int g_is_ipsec_test ; 

__attribute__((used)) static void
setup_ipsec_test(void)
{
	T_LOG("Configuring for ipsec tests");
	g_OPT_ENABLE_NETIF = IPSEC_OPT_ENABLE_NETIF;
	g_OPT_ENABLE_FLOWSWITCH = IPSEC_OPT_ENABLE_FLOWSWITCH;
	g_OPT_ENABLE_CHANNEL = IPSEC_OPT_ENABLE_CHANNEL;
	g_OPT_GET_CHANNEL_UUID = IPSEC_OPT_GET_CHANNEL_UUID;
	g_OPT_IFNAME = IPSEC_OPT_IFNAME;
	g_CONTROL_NAME = IPSEC_CONTROL_NAME;
	g_is_ipsec_test = true;
}