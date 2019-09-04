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
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  UTUN_CONTROL_NAME ; 
 int /*<<< orphan*/  UTUN_OPT_ENABLE_CHANNEL ; 
 int /*<<< orphan*/  UTUN_OPT_ENABLE_FLOWSWITCH ; 
 int /*<<< orphan*/  UTUN_OPT_ENABLE_NETIF ; 
 int /*<<< orphan*/  UTUN_OPT_GET_CHANNEL_UUID ; 
 int /*<<< orphan*/  UTUN_OPT_IFNAME ; 
 int /*<<< orphan*/  g_CONTROL_NAME ; 
 int /*<<< orphan*/  g_OPT_ENABLE_CHANNEL ; 
 int /*<<< orphan*/  g_OPT_ENABLE_FLOWSWITCH ; 
 int /*<<< orphan*/  g_OPT_ENABLE_NETIF ; 
 int /*<<< orphan*/  g_OPT_GET_CHANNEL_UUID ; 
 int /*<<< orphan*/  g_OPT_IFNAME ; 
 int g_is_utun_test ; 

__attribute__((used)) static void
setup_utun_test(void)
{
	T_LOG("Configuring for utun tests");
	g_OPT_ENABLE_NETIF = UTUN_OPT_ENABLE_NETIF;
	g_OPT_ENABLE_FLOWSWITCH = UTUN_OPT_ENABLE_FLOWSWITCH;
	g_OPT_ENABLE_CHANNEL = UTUN_OPT_ENABLE_CHANNEL;
	g_OPT_GET_CHANNEL_UUID = UTUN_OPT_GET_CHANNEL_UUID;
	g_OPT_IFNAME = UTUN_OPT_IFNAME;
	g_CONTROL_NAME = UTUN_CONTROL_NAME;
	g_is_utun_test = true;
}